#ifndef PCISPH_SOLVER_H
#define PCISPH_SOLVER_H

#include "Grid.h"

class PCISPH_Solver
{
	// This solver will be based on the OpenCL lecture
	// I found on YouTube

	// We need to solve 4 equations in a specific order.
	// So all our functions will follow based on these that
	// are need-to-know. Then these will all be called in
	// the main algorithm step. Finally they will be integrated
	// outside of this method in the particle system object...

	// NUMERICAL ALGORITHM FOR SOLVING SPH

public:

	// Unique to PCISPH
	static void solveParticles(std::vector<SPH_Sphere*>* pList, float timeDiff);

	

private:

	// We solve for density using the second equation
	static void solveVelocity(SPH_Sphere* pHood, float timeDiff);
	// We solve for pressure using the k(p - p0) where p is 'ro' or density
	static void solvePressure(SPH_Sphere* pHood);


	static void solveNPForces(SPH_Sphere* pSphere);

	static void predictVelocity(SPH_Sphere* pSphere);

	static void predictPosition(SPH_Sphere* pSphere);

	static void predictDensity(SPH_Sphere* pSphere);

	static float predictDensityVariation(SPH_Sphere* pSphere);

	static void updatePressure(SPH_Sphere* pSphere, float densityError);

	static float Smooth(SPH_Sphere*, SPH_Sphere*);
	static Vec3 DelSmooth(SPH_Sphere*, SPH_Sphere*);

	static float solveCorrectionScalar(SPH_Sphere* pSphere);

	static void solvePressureForce(SPH_Sphere* pSphere);

	static Vec3 privSummation(std::vector<Vec3> inFloats);

	static float privSummation(std::vector<float> inFloats);

	// static void Smooth( some kind of reference );

};

#endif