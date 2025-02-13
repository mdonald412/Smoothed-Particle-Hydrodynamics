//--------------------------------------------------------------

//--------------------------------------------------------------

// Enable data
#define UAV_Positions
#define UAV_Neighbors
#define UAV_Densities
#define UAV_Pressures
#define UAV_Velocities
#define SRV_Positions

// Forces...
#define GRAVITY 2.0f
#define INERTIA 0.8f
#define TIME_STEP 0.005f

#include "ShaderMappings.hlsli"

[numthreads(1, 1, 1)]
void VelocitySolver_Main(uint3 dtID : SV_DispatchThreadID)
{
	// Introduce some check to ensure we don't update velocities of boundary spheres........ 

	int currSphere = dtID.x;

	float4 prevVelocity = VelocitiesBuff[currSphere];
	VelocitiesBuff[currSphere] = PressuresBuff[currSphere]*(1.0f - INERTIA);
	VelocitiesBuff[currSphere].y -= GRAVITY;
	VelocitiesBuff[currSphere] += prevVelocity*INERTIA;
	PositionsBuff[currSphere] = PositionsBuff[currSphere] + VelocitiesBuff[currSphere] * TIME_STEP;


	PressuresBuff[currSphere].xyz = 0.0f;
	DensitiesBuff[currSphere] = 0.0f;
	//PositionsHere[currSphere] = PositionsBuff[currSphere];
}