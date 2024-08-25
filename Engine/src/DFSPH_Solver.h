#ifndef DFSPH_SOLVER
#define DFSPH_SOLVER

#include "GridIterator.h"

class DFSPH_Solver
{
public:

private:

	// STEP 1: Compute non-pressure forces...
	void solverNPForces(Neighborhood* pHood);

	// STEP 2: Predict velocities
	void predictVelocities(Neighborhood* pHood);

	// STEP 3: (Helper) Correct density error
	void correctDensityError(float Factors, SPH_Sphere* currSphere);

	// STEP 4: Now we actually need to rerun the neighborhood solver sooooo.... do that...

	// STEP 5: Update the positions for each particle using this method...
	void updatePosition(SPH_Sphere* inSphere);

	// STEP 6: Compute densities (do this once for each particle at the beginning of the sim too)
	void solveDensity(Neighborhood* pHood);

	// STEP 6: Compute factors (do this once for each particle at the beginning of the sim too)
	void solveFactors(Neighborhood* pHood); // Not sure what we're doing in here yet...

	void updateVelocities(SPH_Sphere* inSphere); // Integrate velocities here at the end before the loop starts over...


private:
	float privSummation(std::vector<float> inFloats);
	Vec3 privSummation(std::vector<Vec3> inFloats);

};

#endif