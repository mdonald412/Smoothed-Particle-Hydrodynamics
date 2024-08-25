//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// Enable data
#define UAV_Positions
#define UAV_Neighbors
#define UAV_Densities
#define UAV_Pressures

#include "ShaderMappings.hlsli"

float Smooth(float cDistance);
float GetMagnitude(float4 vec1, float4 vec2);

[numthreads(1, 1, 1)]
void PressureGradientSolver_Main(uint3 dtID : SV_DispatchThreadID)
{
	int currSphere = dtID.x;
	int currNeighbor = (dtID.x*32) + dtID.y;

	float4 diff =  PositionsBuff[NeighborsBuff[currNeighbor]] - PositionsBuff[currSphere];
	float cDistance = GetMagnitude(PositionsBuff[currSphere], PositionsBuff[NeighborsBuff[currNeighbor]]);

	// Early out here...
	if (cDistance > 1.0f)
	{
	}
	else if (cDistance == 0)
	{
	}
	else
	{
		float cMass = 0.5f;
		float cDensity = DensitiesBuff[currSphere];
		float cPressure = DensitiesBuff[currSphere]; // Right now our resting pressure so these will be the same until we change that....

		float cMass2 = 0.5f;
		float cDensity2 = DensitiesBuff[NeighborsBuff[currNeighbor]];
		float cPressure2 = DensitiesBuff[NeighborsBuff[currNeighbor]];
		
		float4 pressureThing = (cMass2 * ((cPressure /( cDensity + cMass)) + (cPressure2 / (cDensity2 + cMass)))
							 * (-45 / 3.14159f)
							 * pow(1.0f, 6) * pow((1.0f - cDistance), 2)
							 * (diff * (1 / cDistance)));

		PressuresBuff[currSphere] = PressuresBuff[currSphere] + pressureThing; // We need to really zero this out...

		// Apply forces from viscosity here... I guess but I don't know...
	}

	//	   |||| | | |  |  |   | <-- Handle a boundary like a linear gradient or whatever you wanna call it...

}

float GetMagnitude(float4 vec1, float4 vec2)
{
	return sqrt(pow((vec1.x - vec2.x), 2) + pow((vec1.y - vec2.y), 2) + pow((vec1.z - vec2.z), 2));
}