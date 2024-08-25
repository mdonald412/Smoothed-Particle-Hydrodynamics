#include "DFSPH_Solver.h"

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

		Vec3 diff = currNeighbor->position - currSphere->position;
		float cDistance = diff.len();

		// Early out here...
		if (cDistance > SMOOTH_RADIUS)
		{
			i++;
			continue;
		}

		if (diff.x() != diff.x())
		{
			Trace::out("Hello");
		}

		float cMass = currNeighbor->mass;

		pressures.push_back(cMass * (315 / (64 * Azul::MATH_PI * pow(cSmooth, 9))) * pow((pow(cSmooth, 2) - pow(cDistance, 2)), 3));

		i++;
		j++;
	}

	float pressureSum = privSummation(pressures);
	if (pressureSum != pressureSum)
	{
		Trace::out("Hello");
	}
	pHood->pSphere->density = pressureSum;
	pHood->pSphere->pressure = pressureSum - RESTING_PRESSURE;
}