#include "SPHMan.h"
#include "MeshProto.h"
#include "MeshNodeMan.h"
#include "GraphicsObject_LightTexture.h"
#include "ShaderObjectNodeMan.h"
#include "TexNodeMan.h"
#include "GameObjectBasic.h"
#include "GameObjectSphere.h"
#include "GameObjectMan.h"
#include "GridIterator.h"
#include "WCSPH_Solver.h"
#include "PCISPH_Solver.h"
#include "ShaderMappings.h"
#include "WCSPH_Compute.h"
#include "DirectXDeviceMan.h"

#define SPRING 0.67f

using namespace Azul;

SPHMan* SPHMan::posInstance = nullptr;

Vec3 Adder(0.01f, 0.03f, 0.02f);

SPHMan::SPHMan()
{
	int iter = 0;
	this->spheresGrid = new Grid();

	computeSolver = new WCSPH_Compute();

	if (NUM_SPHERES)
	{
		WCSPH_Solver::initalize(FRAME_COUNT);
		WCSPH_Compute::initalize(FRAME_COUNT);

		GameObjectSphere::Initialize(NUM_SPHERES);
		int maxSpheres = pow(GRID_MAX, 3);
		Vec3 lightColor(1, 0, 0);
		this->pGameObj = new GameObjectSphere(lightColor, 2);
		GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
	}
}

// Manager Stuff...

void SPHMan::Create()
{
	if (posInstance == nullptr)
	{
		posInstance = new SPHMan();
	}
}

void Azul::SPHMan::Destroy()
{
	if (posInstance)
	{
		delete posInstance;
	}
}

SPHMan::~SPHMan()
{
	delete this->spheresGrid;
	//delete //this->spheresList;
	int i = 0;
	while (i < this->spheresList.size())
	{
		delete spheresList.at(i);
		i++;
	}

	delete this->computeSolver;
}

SPHMan* Azul::SPHMan::privGetInstance()
{
	assert(posInstance);
	return posInstance;
}

// Utilities...

SPH_Sphere* SPHMan::AddSphere(float _mass, Vec3 _position, float _radius, SPH_Sphere::Type type)
{
	SPHMan* sphMan = privGetInstance();

	SPH_Sphere* newSphere = new SPH_Sphere();
	newSphere->mass = _mass;
	*newSphere->position = _position;
	newSphere->radius = _radius;
	newSphere->type = type;

	Vec3 lightColor(0.0f, 0.0f, 1.0f);
	sphMan->spheresList.push_back(newSphere);

	if (type == SPH_Sphere::Type::Active)
	{
		sphMan->pGameObj->AddSphere(newSphere);
	}
	else
	{
		newSphere->index = 4097; // Out of scope of simulation...
	}

	return newSphere;
}


// Getters ...

Grid* Azul::SPHMan::GetSpheresGrid()
{
	SPHMan* sphMan = privGetInstance();

	return sphMan->spheresGrid;
}

std::vector<SPH_Sphere*> Azul::SPHMan::GetSpheresList()
{
	SPHMan* sphMan = privGetInstance();

	return sphMan->spheresList;
}


// Simulation step:

void Azul::SPHMan::Update(Azul::AnimTime animTime)
{
	// Iterate through balls and bounce them
	SPHMan* sphMan = privGetInstance();

	float timeDiff = TIME_STEP;

	//////////////////////
	// INSERT INTO GRID //
	//////////////////////

	SPHMan::FillNeighborhood();
	
	///////////////////////
	// ADVANCE POSITIONS //
	///////////////////////


	SPH_Strategy::solveParticles(&sphMan->spheresList);


	//WCSPH_Solver::solveParticles(&sphMan->spheresList);


	//WCSPH_Compute::solveParticles(&sphMan->spheresList);


	///////////////////////
	// CORRECT POSITIONS //
	///////////////////////

	SPHMan::FixPositions();


	sphMan->spheresGrid->Clear();

}

// Update helpers...

void SPHMan::FillNeighborhood()
{
	SPHMan* sphMan = privGetInstance();

	// Fills the grid...

	int iter = 0;
	while (iter < sphMan->spheresList.size())
	{
		SPH_Sphere* addSphere = sphMan->spheresList.at(iter);

		sphMan->spheresGrid->BoundedX(addSphere);
		sphMan->spheresGrid->BoundedY(addSphere);
		sphMan->spheresGrid->BoundedZ(addSphere);

		sphMan->spheresGrid->Insert(addSphere);
		sphMan->spheresList.at(iter)->color = Vec3(1.0f, 0.0f, 0.0f);
		iter++;
	}

	// Updates the spheres neighborslist...

	GridIterator* gridIterator = sphMan->spheresGrid->getIterator();

	// Soooo for now we're gonna load up the sphere with it's neighborlist.. so we're gonna...
	// So we gonna put them in there and then we'll have them wahoo... This needs to change in the future...
	for (Neighborhood hood = gridIterator->First(); !gridIterator->IsDone(); hood = gridIterator->Next())
	{
		//std::vector<SPH_Sphere*> pNeighbors = hood.neighbors; // Let's see if this works....
		*hood.pSphere->neighborsList = hood.neighbors; // Something going wrong here??
	}
}


void SPHMan::FixPositions()
{
	SPHMan* sphMan = privGetInstance();

	int iter = 0;
	while (iter < sphMan->spheresList.size())
	{
		SPH_Sphere* sphere_01 = sphMan->spheresList.at(iter);

		Grid* thisGrid = sphMan->spheresGrid;

		//float diffTime = AnimTime(AnimTime::Duration::NTSC_FRAME) / AnimTime(AnimTime::Duration::ONE_SECOND);
		//sphere_01->Velocity += Vec3((GRAVITY * diffTime), (GRAVITY * diffTime),(GRAVITY * diffTime));
		//Vec3 target = sphere_01->position;
		thisGrid->BoundedX(sphere_01);
		thisGrid->BoundedY(sphere_01);
		thisGrid->BoundedZ(sphere_01);
		//sphere_01->position = target;
		iter++;
	}
}


//// THIS FUNCTION WILL EVENTUALLY HELP US DEFINE A GRID...
//Vec3 SPHMan::randVec(int constraint)
//{
//	int GridLengthX = GRID_MAX * SMOOTH_RADIUS;
//	int GridLengthY = GRID_MAX * SMOOTH_RADIUS;
//	int GridLengthZ = GRID_MAX * SMOOTH_RADIUS;
//
//	int onX = constraint % GridLengthX;
//	int onY = (int)(constraint / GridLengthY)%GridLengthX;
//	int onZ = constraint / (GridLengthX*GridLengthY);
//
//	return Vec3((onX - GridLengthX/2 + 0.1f), (onY - GridLengthY/2 + 0.1f), (onZ - GridLengthZ/2 + 0.1f));
//}