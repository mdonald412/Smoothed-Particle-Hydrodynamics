#include "WCSPH_Solver.h"
#include "SPH_Stats.h"
#define PI 3.1415926f

Vec3* WCSPH_Solver::pBuffer;

void WCSPH_Solver::initalize(int count)
{
	SPH_Strategy::initialize(count);
	WCSPH_Solver::pBuffer = new Vec3[NUM_SPHERES];
}

void WCSPH_Solver::Destroy()
{
	delete[] pBuffer;
}

void WCSPH_Solver::solveParticles(std::vector<SPH_Sphere*>* pList)
{
	int i = 0;
	while (i < pList->size())
	{
		// Calculate velocity here...
		WCSPH_Solver::solvePressure(pList->at(i));
		i++;
	}

	i = 0;
	while (i < pList->size())
	{
		// Calculate pressure here...
		WCSPH_Solver::solvePressureGradient(pList->at(i));
		i++;
	}

	i = 0;
	while (i < pList->size())
	{
		// Calculate velocity here...
		WCSPH_Solver::solveVelocity(pList->at(i), TIME_STEP);
		i++;
	}

	i = 0;
	while (i < NUM_SPHERES)
	{

		pBuffer[i] = *pList->at(i)->position;
		i++;
	}


	SPH_Strategy::RecordFrame(pBuffer); // Pass in the positions just created in the last step...
	SPH_Strategy::frame++;
}

// Return velocity differential here...
void WCSPH_Solver::solveVelocity(SPH_Sphere* pSphere, float timeDiff)
{
	// How do we add inertia?
	if (pSphere->type == SPH_Sphere::Type::Active)
	{
		Vec3 prevVelocity = *pSphere->Velocity;
		
		// Determine boundary force here....


		Vec3 acceleration = ((*pSphere->PressureForce) + Vec3(0, GRAVITY, 0)) *(1/0.5f);
		*pSphere->Velocity = acceleration*timeDiff*(1.0f - INERTIA) + prevVelocity * INERTIA;// -hood.pSphere->Viscosity;

		*pSphere->position += ((*pSphere->Velocity) * timeDiff);
	}
}


void WCSPH_Solver::solvePressureGradient(SPH_Sphere* pSphere)
{
	std::vector<Vec3> pressures;
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
		cDistance = GetMagnitude(*currNeighbor->position, *currSphere->position);
		if (cDistance == 0.0f)
		{
			cDistance = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.00025f));
			float random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.00025f));
			diff = Vec3(random, random + 0.1f, random);
		}

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

		float cMass = currSphere->mass;
		float cDensity = currSphere->density;
		float cPressure = currSphere->pressure;

		float cMass2 = currNeighbor->mass;
		float cDensity2 = currNeighbor->density;
		float cPressure2 = currNeighbor->pressure;
		
		Vec3 pressureThing = (cMass2 * ((cPressure /( cDensity + currSphere->mass)) + (cPressure2 / (cDensity2 + currSphere->mass)))
			* (-45 / Azul::MATH_PI)
			* pow(cSmooth, 6) * pow((cSmooth - cDistance), 2)
			* (diff * (1 / cDistance)));

		pressures.push_back(pressureThing);

	

		i++;

	}

	*currSphere->PressureForce = privSummation(pressures);

}

void WCSPH_Solver::solvePressure(SPH_Sphere* pSphere)
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
		
		float peekSmooth = (315 / (64 * Azul::MATH_PI * pow(cSmooth, 9)))* pow((pow(cSmooth, 2) - pow(cDistance, 2)), 3); // Check this value against what the shader makes...
		pressures.push_back(cMass * (315 / (64 * Azul::MATH_PI* pow(cSmooth, 9))) * pow((pow(cSmooth, 2) - pow(cDistance, 2)), 3));

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
}

void WCSPH_Solver::solveViscosity(SPH_Sphere* pSphere)
{
	std::vector<Vec3> viscos;
	viscos.reserve(pSphere->neighborsList->size());

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
		if (cDistance == 0.0f)
		{
			cDistance = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.00025f));
			float random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.00025f));
			diff = Vec3(random, random, random);
		}

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

		float cMass = currNeighbor->mass;        // j
		Vec3 cVelocity1 = *currNeighbor->Velocity;//j
		Vec3 cVelocity2 = *currSphere->Velocity; // i
		float cDensity = currNeighbor->density; // Something with density is causing this issue.

		float term1 = cMass;

		Vec3 term2 = cVelocity1 - cVelocity2;
		term2[x] /= cDensity;
		term2[y] /= cDensity;
		term2[z] /= cDensity;

		float term3 = 45 / (Azul::MATH_PI * pow(SMOOTH_RADIUS, 6));

		float term4 = SMOOTH_RADIUS - cDistance;

		Vec3 visco = term1 * term2 * term3 * term4 * 0.05f;

		viscos.push_back(visco); // This is the term that makes it a vector apparently...

		i++;

	}

	float cViscosityCoefficient = 0.05f; // Experiment with this I guess...
	//float density = currSphere->density + 0.0001f;


	*currSphere->Viscosity = (cViscosityCoefficient)*privSummation(viscos);
}


Vec3 WCSPH_Solver::privSummation(std::vector<Vec3> inVecs)
{
	Vec3 returnValue = Vec3(0.0f,0.0f,0.0f);

	int i = 0;
	while (i < inVecs.size())
	{
		returnValue += inVecs[i];
		i++;
	}

	return returnValue;
}

float WCSPH_Solver::privSummation(std::vector<float> inFloats)
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

float WCSPH_Solver::GetMagnitude(Vec3 vec1, Vec3 vec2)
{
	return sqrt(pow((vec1.x() - vec2.x()), 2) + pow((vec1.y() - vec2.y()), 2) + pow((vec1.z() - vec2.z()), 2));
}