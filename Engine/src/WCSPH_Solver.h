#ifndef WCSPH_Solver_H
 #define WCSPH_Solver_H

#include "SPH_Strategy.h"

class WCSPH_Solver : public SPH_Strategy
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

	static void initalize(int);
	static void Destroy();

	static void solveParticles(std::vector<SPH_Sphere*>* pList);


		// We solve for density using the second equation
	static void solveVelocity(SPH_Sphere* pHood, float timeDiff);
		// We solve for pressure using the k(p - p0) where p is 'ro' or density
	static void solvePressure(SPH_Sphere* pHood);
		// We solve for the pressure gradient using equation 3
	static void solvePressureGradient(SPH_Sphere* pHood);
		// We solve for the viscous term using equation 4
	static void solveViscosity(SPH_Sphere* pHood);

private:
	static Vec3 privSummation(std::vector<Vec3> inFloats);

	static float privSummation(std::vector<float> inFloats);

	static float GetMagnitude(Vec3, Vec3);

	static Vec3* pBuffer;



};

#endif