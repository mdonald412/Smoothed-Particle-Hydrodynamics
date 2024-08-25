#include "WCSPH_Compute.h"
#include "SPH_Stats.h"
#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "ComputeCBVBuffer.h"
#include "MathEngine.h"
#include "SPH_Spheres.h"

Azul::WCSPH_Compute::WCSPH_Compute()
	: neighbors(nullptr),
	positions(nullptr),
	velocities(nullptr),
	densities(nullptr),
	pressures(nullptr)
{
	this->neighbors = new ComputeRSVBuffer(NUM_SPHERES, 48); // 48  max number of neighbors? Maybe? Check ...
	this->positions = new ComputeUAVBuffer(NUM_SPHERES, sizeof(Vec4)); // These will need to be transferred and passed back for neighborSearch...
	this->velocities = new ComputeUAVBuffer(NUM_SPHERES, sizeof(Vec4)); // These will need to be transferred...
	this->densities = new ComputeUAVBuffer(NUM_SPHERES, sizeof(float)); // No need to transfer on every step, just at the beginning..
	this->pressures = new ComputeUAVBuffer(NUM_SPHERES, sizeof(float)); // No need to transfer on every step, just at the beginning...
}


void Azul::WCSPH_Compute::Load(SPH_Sphere::NeighborID* pNeighborBuff, Vec3* pPositionBuff, Vec3* pVelocitiesBuff)
{
	this->neighbors->Transfer(pNeighborBuff);
	this->positions->Transfer(pPositionBuff);
}
