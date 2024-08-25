#include "PCISPH_Solver.h"
#include "SPH_Stats.h"
#define PI 3.1415926f

void PCISPH_Solver::solveParticles(std::vector<SPH_Sphere*>* pList, float timeDiff)
{

	int i = 0;
	int max = pList->size();
	while (i < max)
	{
		// For all particles solve non-pressure forces...

		PCISPH_Solver::solveNPForces(pList->at(i));
		pList->at(i)->pressure = 0.0f;
		*pList->at(i)->PressureForce = Vec3(0.0f, 0.0f, 0.0f);

		i++;

	}

	// Jacobi iteration here...
	int iter = 0;
	float densityError = 0.0f;
	float indivDensityError = 0.0f;
	while (densityError > MAX_ERROR || iter < MIN_ITERATIONS)
	{
		densityError = 0.0f;
		i = 0;
		max = pList->size();
		while (i < max)
		{
			// For all particles predict velocity and position...
			pList->at(i)->pressure = std::min(0.0f, pList->at(i)->pressure);
	
			predictVelocity(pList->at(i));
			predictPosition(pList->at(i));
			i++;

		}

		i = 0;
		while (i < pList->size())
		{
			// For all particles predict velocity and position...

			predictDensity(pList->at(i));
			indivDensityError = std::max(predictDensityVariation(pList->at(i)), 0.0f);
			if (pList->at(i)->type != SPH_Sphere::Static)
			{
				densityError += indivDensityError;
			}
			updatePressure(pList->at(i), indivDensityError);
			i++;

		}

		i = 0;
		while (i < pList->size())
		{
			// For all particles predict velocity and position...

			solvePressureForce(pList->at(i));
			if (pList->at(i)->PressureForce->len() > 100.0f)
			{
				//Trace::out("Hello");
			}
			i++;
		}

		iter++;

	}

	i = 0;
	while (i < pList->size())
	{
		// For all particles predict velocity and position...

		solveVelocity(pList->at(i), TIME_STEP);
		i++;

	}

	i = 0;
	while (i < pList->size())
	{
		// For all particles predict velocity and position...
		SPH_Sphere* currSphere = pList->at(i);

		int j = 0;
		int max = currSphere->neighborsList->size();
		while (j < max)
		{
			SPH_Sphere* currNeighbor = currSphere->neighborsList->at(j);

			if (currNeighbor->type == SPH_Sphere::Type::Dynamic)
			{
				delete currNeighbor;
			}

			j++;
		}

		i++;

	}

}

void PCISPH_Solver::solveNPForces(SPH_Sphere* pSphere)
{
	*pSphere->NonPressureForces = Vec3(0.0f, GRAVITY, 0.0f);
}

void PCISPH_Solver::predictVelocity(SPH_Sphere* pSphere)
{
	if (pSphere->type != SPH_Sphere::Static)
	{
		Vec3 acceleration = ((*pSphere->PressureForce + *pSphere->NonPressureForces) * (1 / pSphere->mass));
		*pSphere->PreVelocity = *pSphere->Velocity + acceleration * TIME_STEP;
	}
	else
	{
		*pSphere->Velocity = Vec3(0.0f, 0.0f, 0.0f);
		*pSphere->PreVelocity = Vec3(0.0f, 0.0f, 0.0f);
	}
}

void PCISPH_Solver::predictPosition(SPH_Sphere* pSphere)
{
	*pSphere->PrePosition = *pSphere->position + *pSphere->PreVelocity*TIME_STEP;
}

void PCISPH_Solver::predictDensity(SPH_Sphere* pSphere)
{
	std::vector<float> densities;
	densities.reserve(pSphere->neighborsList->size());

	SPH_Sphere* currSphere = pSphere;

	float cSmooth = SMOOTH_RADIUS;

	// Create summation...
	int max = pSphere->neighborsList->size();
	int i = 0;
	int j = 0;
	while (i < max)
	{
		// Solve Pressure individual calculation...
		SPH_Sphere* currNeighbor = pSphere->neighborsList->at(i);

		Vec3 diff = *currNeighbor->PrePosition - *currSphere->PrePosition;
		float cDistance = sqrt(pow(diff[x], 2) + pow(diff[y], 2) + pow(diff[z], 2));

		// Early out here...
		if (cDistance > SMOOTH_RADIUS) // Should push this check to the neighborList filling...
		{
			i++;
			continue;
		}

		float cMass = currNeighbor->mass;

		densities.push_back(cMass * (315 / (64 * Azul::MATH_PI * pow(cSmooth, 9))) * pow((pow(cSmooth, 2) - pow(cDistance, 2)), 3));

		i++;
		j++;
	}

	float densitySum = privSummation(densities);
	pSphere->PreDensity = densitySum;
}

float PCISPH_Solver::predictDensityVariation(SPH_Sphere* pSphere)
{
	if (pSphere->PreDensity < RESTING_DENSITY)
	{
		//Trace::out("Hello");
	}
	return pSphere->PreDensity - RESTING_DENSITY;
}

void PCISPH_Solver::updatePressure(SPH_Sphere* pSphere, float densityError)
{
	// Apply force to current sphere...

	float correctionScalar = solveCorrectionScalar(pSphere); // The problem is here with our correction scalar....
	pSphere->pressure += densityError*correctionScalar;
}

float PCISPH_Solver::solveCorrectionScalar(SPH_Sphere* pSphere)
{
	float beta = pow(TIME_STEP, 2) * pow(pSphere->mass, 2) * (2 / pow(RESTING_DENSITY, 2));
	
	Vec3 Summation1 = Vec3();
	float Summation2 = 0.0f;
	std::vector<SPH_Sphere*>* pNeighbors = pSphere->neighborsList;

	int i = 0;
	int max = pNeighbors->size();
	while (i < max)
	{
		Summation1 += DelSmooth(pSphere, pNeighbors->at(i));

		i++;
	}

	i = 0;
	max = pNeighbors->size();
	while (i < max)
	{
		Summation2 += (DelSmooth(pSphere, pNeighbors->at(i)).dot(DelSmooth(pSphere, pNeighbors->at(i))));

		i++;
	}
	if (max == 0)
	{
		return 0;
	}
	else
	{
		float outValue1 = (beta * (-Summation1.dot(Summation1) - Summation2));
		if (outValue1 == 0.0f)
		{
			return 0.0f;
		}
		float outValue =  -1 /outValue1;
		return outValue;
	}

}

void PCISPH_Solver::solvePressureForce(SPH_Sphere* pSphere)
{
	Vec3* pressureForces = pSphere->PressureForce;
	Vec3* neighborPressureForces;

	SPH_Sphere* pNeighbor;

	std::vector<SPH_Sphere*>* pNeighbors = pSphere->neighborsList;
	int i = 0;
	int max = pNeighbors->size();

	Vec3 smoothSummation;

	while (i < max)
	{
		pNeighbor = pNeighbors->at(i);

		Vec3 smooth = DelSmooth(pSphere, pNeighbor);
		Vec3 adder = smooth;

		smoothSummation += smooth;
		i++;
	}
	float middleTerm;
	if (pSphere->pressure != 0)
	{
		middleTerm = (2 * pSphere->pressure) / pow(pSphere->PreDensity, 2);
	}
	else
	{
		middleTerm = 0.0f;
	}

	// THERE IS SOME ISSUE GOING ON HERE... particles are converging insteading pushing against each other...


	Vec3 smoothPressureForce = pow(pSphere->mass, 2) * middleTerm * smoothSummation;

	*pressureForces += (smoothPressureForce * (1.0f/2.0f));

	i = 0;
	while (i < max)
	{
		pNeighbor = pNeighbors->at(i);
		neighborPressureForces = pNeighbor->PressureForce;
		
		Vec3 smooth = DelSmooth(pNeighbor, pSphere);

		float middleTerm1;
		if (pNeighbor->pressure != 0)
		{
			middleTerm1 = (2 * pNeighbor->pressure) / pow(pNeighbor->PreDensity, 2);
		}
		else
		{
			middleTerm1 = 0.0f;
		}

		Vec3 smoothNeighborForce = pow(pSphere->mass, 2) * middleTerm1 * (smooth);
		if (pNeighbor->type == SPH_Sphere::Type::Dynamic)
		{
			*pressureForces += ((pow(pSphere->mass, 2) * middleTerm * smoothSummation) * (1.0f / 2.0f));
		}

		*neighborPressureForces -= smoothNeighborForce * (1.0f / 2.0f);
		i++;
	}

}

// Return velocity differential here...
void PCISPH_Solver::solveVelocity(SPH_Sphere* pSphere, float timeDiff)
{
	// How do we add inertia?
	if (pSphere->type != SPH_Sphere::Type::Static)
	{
		Vec3 prevVelocity = *pSphere->Velocity;
		Vec3 acceleration = ((*pSphere->PressureForce + *pSphere->NonPressureForces) * (1 / pSphere->mass));

		*pSphere->Velocity = acceleration * TIME_STEP;
		if (pSphere->Velocity->len() * TIME_STEP > 0.5f)
		{
			//Trace::out("Hello");
		}
		*pSphere->position += ((*pSphere->Velocity) * TIME_STEP);
	}

}

void PCISPH_Solver::solvePressure(SPH_Sphere* pSphere)
{
	std::vector<float> pressures;
	pressures.reserve(pSphere->neighborsList->size());

	SPH_Sphere* currSphere = pSphere;

	float cSmooth = SMOOTH_RADIUS;

	// Create summation...
	int max = pSphere->neighborsList->size();
	int i = 0;
	int j = 0;
	while (i < max)
	{
		// Solve Pressure individual calculation...
		SPH_Sphere* currNeighbor = pSphere->neighborsList->at(i);

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
	pSphere->density = pressureSum;
	pSphere->pressure = pressureSum - RESTING_PRESSURE;

	if (pSphere->pressure > 0.0f)
	{
		//Trace::out("Hello");
	}
}

Vec3 PCISPH_Solver::privSummation(std::vector<Vec3> inVecs)
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

float PCISPH_Solver::privSummation(std::vector<float> inFloats)
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

float PCISPH_Solver::Smooth(SPH_Sphere* currSphere, SPH_Sphere* currNeighbor)
{
	Vec3 diff = *currNeighbor->position - *currSphere->position;
	float cDistance = diff.len();

	if (cDistance < SMOOTH_RADIUS)
	{
		return (315 / (64 * Azul::MATH_PI * pow(SMOOTH_RADIUS, 9))) * pow((pow(SMOOTH_RADIUS, 2) - pow(cDistance, 2)), 3);
	}
	else
	{
		return 0;
	}
}

Vec3 PCISPH_Solver::DelSmooth(SPH_Sphere* currSphere, SPH_Sphere* currNeighbor)
{
	Vec3 diff = *currNeighbor->position - *currSphere->position;
	float cDistance = diff.len();

	if (cDistance < SMOOTH_RADIUS)
	{
		return (-45 / (Azul::MATH_PI * pow(SMOOTH_RADIUS, 6)))
			* pow((SMOOTH_RADIUS - cDistance), 2)
			* (diff * (1 / cDistance));
	}
	else
	{
		return Vec3(0, 0, 0);
	}
}