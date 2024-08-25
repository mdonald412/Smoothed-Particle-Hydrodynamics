//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// Enable data
#define UAV_Positions
#define UAV_Neighbors
#define UAV_Densities

#include "ShaderMappings.hlsli"

float Smooth(float cDistance);
float GetMagnitude(float4 vec1, float4 vec2);

[numthreads(1, 1, 1)]
void DensitySolver_Main(uint3 dtID : SV_DispatchThreadID)
{
	// Get indices of currenty sphere and neighbor sphere index...
	uint spheresIndex = dtID.x;
	uint neighborIndex = (dtID.x*32) + dtID.y;

	float4 diff = PositionsBuff[spheresIndex].xyzw - PositionsBuff[NeighborsBuff[neighborIndex]].xyzw;
	float cDistance = GetMagnitude(PositionsBuff[spheresIndex], PositionsBuff[NeighborsBuff[neighborIndex]]); // Should return the magnitude of this vector...
	float cMass = 0.5f;
	float smootherVal = Smooth(cDistance);
	
	if (NeighborsBuff[neighborIndex] == -1)
	{
		// This means there is no neighbor here....
	}
	else if (cDistance > 1.0f)
	{
	
	}
	else
	{
		float summationAddVal = cMass * smootherVal;
		DensitiesBuff[spheresIndex] = DensitiesBuff[spheresIndex] + summationAddVal;
		//DensitiesBuff[spheresIndex] = cDistance;
		
	}
}


float Smooth(float cDistance)
{
	float cSmooth = 1.0f; // This is constant so I need to define this elsewhere...
	return (315 / (64 * 3.14159f* pow(cSmooth, 9))) * pow((pow(cSmooth, 2) - pow(cDistance, 2)), 3);
}

float GetMagnitude(float4 vec1, float4 vec2)
{
	return sqrt(pow((vec1.x - vec2.x), 2) + pow((vec1.y - vec2.y), 2) + pow((vec1.z - vec2.z), 2));
}