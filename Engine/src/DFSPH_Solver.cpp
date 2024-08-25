#include "DFSPH_Solver.h"

void DFSPH_Solver::solverNPForces(Neighborhood* pHood)
{
	// TODO: gravity, surface tension and viscosity...
	SPH_Sphere* currSphere = pHood->pSphere;
	*currSphere->NonPressureForces = Vec3(0.0f, -GRAVITY, 0.0f);
}

void DFSPH_Solver::predictVelocities(Neighborhood* pHood)
{
	*pHood->pSphere->Velocity += (*(pHood->pSphere->PressureForce)*TIME_STEP);
}

// This one is a little weird... cuz we need the whoooole frickin pressure field in here...
void DFSPH_Solver::correctDensityError(float Factors, SPH_Sphere* currSphere)
{
	
}

void DFSPH_Solver::solveDensity(Neighborhood* pHood)
{
	std::vector<float> pressures;
	pressures.reserve(pHood->neighbors.size());

	SPH_Sphere* currSphere = pHood->pSphere;

	float cSmooth = SMOOTH_RADIUS;

	// Create summation...
	int max = pHood->neighbors.size();
	int i = 0;
	int j = 0;
	while (i < max)
	{
		// Solve Pressure individual calculation...
		SPH_Sphere* currNeighbor = pHood->neighbors[i];

		Vec3 diff = *currNeighbor->position - *currSphere->position;
		float cDistance = diff.len();

		// Early out here...
		if (cDistance > SMOOTH_RADIUS)
		{
			i++;
			continue;
		}

		if (diff.x() != diff.x())
		{
			//Trace::out("Hello");
		}

		float cMass = currNeighbor->mass;

		pressures.push_back(cMass * (315 / (64 * Azul::MATH_PI * pow(cSmooth, 9))) * pow((pow(cSmooth, 2) - pow(cDistance, 2)), 3));

		i++;
		j++;
	}

	float pressureSum = privSummation(pressures);
	if (pressureSum != pressureSum)
	{
		//Trace::out("Hello");
	}

	pHood->pSphere->density = pressureSum;
	pHood->pSphere->pressure = pressureSum - RESTING_PRESSURE; // Not sure if we need this for DF at the moment...
}




Vec3 DFSPH_Solver::privSummation(std::vector<Vec3> inVecs)
{
	Vec3 returnValue = Vec3(0.0f, 0.0f, 0.0f);

	int i = 0;
	while (i < inVecs.size())
	{
		returnValue += inVecs[i];
		i++;
	}

	return returnValue;
}


float DFSPH_Solver::privSummation(std::vector<float> inFloats)
{
	float returnValue = 0.0f;

	int i = 0;
	while (i < inFloats.size())
	{
		returnValue += inFloats[i];
		i++;
	}

	return returnValue;
}