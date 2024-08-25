#include "WCSPH_Compute.h"
#include "SPH_Stats.h"
#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "ComputeCBVBuffer.h"
#include "MathEngine.h"
#include "SPH_Spheres.h"
#include "SPHMan.h"
#include "ShaderObjectNodeMan.h"
#include "DirectXDeviceMan.h"

ComputeUAVBuffer* WCSPH_Compute::UAV_Neighbors;
ComputeUAVBuffer* WCSPH_Compute::UAV_Positions;
ComputeUAVBuffer* WCSPH_Compute::UAV_Velocities;
ComputeUAVBuffer* WCSPH_Compute::UAV_Densities;
ComputeUAVBuffer* WCSPH_Compute::UAV_Pressures;
ComputeRSVBuffer* WCSPH_Compute::RSV_Positions;

char* WCSPH_Compute::pBuffer;
SPH_Sphere::NeighborID* WCSPH_Compute::NeighborBuff;
Vec3* WCSPH_Compute::positionsBuff;

Azul::WCSPH_Compute::WCSPH_Compute()
{
	this->UAV_Neighbors = new ComputeUAVBuffer(NUM_SPHERES*32, sizeof(int)); // 48  max number of neighbors? Maybe? Check ...
	this->UAV_Positions = new ComputeUAVBuffer(NUM_SPHERES, sizeof(Vec4)); // These will need to be transferred and passed back for neighborSearch...
	this->UAV_Velocities = new ComputeUAVBuffer(NUM_SPHERES, sizeof(Vec4)); // These will need to be transferred...
	this->UAV_Densities = new ComputeUAVBuffer(NUM_SPHERES, sizeof(float)); // No need to transfer on every step, just at the beginning..
	this->UAV_Pressures = new ComputeUAVBuffer(NUM_SPHERES, sizeof(Vec4)); // No need to transfer on every step, just at the beginning...

	pBuffer = new char[NUM_SPHERES * 16];
	NeighborBuff = new int[NUM_SPHERES * NUM_NEIGHBORS]();
	positionsBuff = new Vec3[NUM_SPHERES]();
}

Azul::WCSPH_Compute::~WCSPH_Compute()
{
	delete this->UAV_Neighbors;
	delete this->UAV_Positions;
	delete this->UAV_Velocities;
	delete this->UAV_Densities;
	delete this->UAV_Pressures;

	delete[] pBuffer;
	delete[] NeighborBuff;
	delete[] positionsBuff;
}

void Azul::WCSPH_Compute::initalize(int count)
{
	SPH_Strategy::initialize(count);
}


void WCSPH_Compute::solveParticles(std::vector<SPH_Sphere*>* myList)
{
	// ------------------------------------------------
		//  execute Compute Shader 
		// ------------------------------------------------
	//SPHMan* sphMan = privGetInstance();

	// Right here I guess we need to load a bunch of damn buffers....

	int size = NUM_SPHERES * NUM_NEIGHBORS;
	//SPH_Sphere::NeighborID* NeighborBuff = new int[NUM_SPHERES * NUM_NEIGHBORS]();
	//Vec3* positionsBuff = new Vec3[NUM_SPHERES]();

	int i = 0;
	int max = (int)myList->size();
	//std::vector<SPH_Sphere*> myList = _myList;
	while (i < myList->size())
	{
		positionsBuff[i] = *myList->at(i)->position;

		int j = 0;
		while (j < NUM_NEIGHBORS)
		{
			int neighborsMax = (int)(myList->at(i)->neighborsList->size());
			if (j >= neighborsMax)
			{
				NeighborBuff[i * NUM_NEIGHBORS + j] = -1;
				j++;
				continue;
			}
			NeighborBuff[i * NUM_NEIGHBORS + j] = myList->at(i)->neighborsList->at(j)->index; // For this to work the index of the sphere must correspond to the order of the sphereslist...
			j++;
		}
		i++;
	}

	Load(NeighborBuff, positionsBuff);

	ShaderObject* pShaderObj = ShaderObjectNodeMan::Find(ShaderObject::Name::DensityCompute);
	pShaderObj->ActivateCSShader();

	UAV_Positions->BindCompute(UnorderedAccessBufferSlot::Positions);

	UAV_Neighbors->BindCompute(UnorderedAccessBufferSlot::Neighbors);

	UAV_Densities->BindCompute(UnorderedAccessBufferSlot::Densities);

	UAV_Pressures->BindCompute(UnorderedAccessBufferSlot::Pressures);

	UAV_Velocities->BindCompute(UnorderedAccessBufferSlot::Velocities);

	// Dispatch with number as spheres as first entry, number of neighbors to compute as second entry...
	DirectXDeviceMan::GetContext()->Dispatch(NUM_SPHERES, NUM_NEIGHBORS, 1); // So this will only dispatch our density solver for right now...

	pShaderObj = ShaderObjectNodeMan::Find(ShaderObject::Name::PressureGradientCompute);
	pShaderObj->ActivateCSShader();

	DirectXDeviceMan::GetContext()->Dispatch(NUM_SPHERES, NUM_NEIGHBORS, 1); // So this will only dispatch our density solver for right now...

	pShaderObj = ShaderObjectNodeMan::Find(ShaderObject::Name::VelocityCompute);
	pShaderObj->ActivateCSShader();

	DirectXDeviceMan::GetContext()->Dispatch(NUM_SPHERES, 1, 1); // So this will only dispatch our density solver for right now...

	UAV_Positions->Map(pBuffer, NUM_SPHERES * 16);

	Vec3* newPositions = (Vec3*)pBuffer;
	i = 0;

	while (i < myList->size())
	{
		*myList->at(i)->position = newPositions[i];

		i++;
	}

	SPH_Strategy::RecordFrame(newPositions); // Record frame...
	SPH_Strategy::frame++;
}


void Azul::WCSPH_Compute::Load(SPH_Sphere::NeighborID* pNeighborBuff, Vec3* pPositionsBuff)
{
	// We need to transfer these before firing off any shaders...
	UAV_Neighbors->Transfer(pNeighborBuff);
	UAV_Positions->Transfer(pPositionsBuff);
}