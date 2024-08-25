#ifndef WCSPH_COMPUTE
#define WCSPH_COMPUTE

#include "SPH_Spheres.h"

namespace Azul
{
	class ComputeRSVBuffer;
	class ComputeUAVBuffer;
	class ComputeCBVBuffer;

	class WCSPH_Compute
	{
	public:
		WCSPH_Compute();
		WCSPH_Compute& operator=(WCSPH_Compute&) = default;
		WCSPH_Compute(WCSPH_Compute&) = default;
		~WCSPH_Compute() = default;

		// Transfer data ... and provide buffers here I guess... although maybe I can call "Load" or something and have
		// it all written in here...

		void Load(SPH_Sphere::NeighborID* pNeighborBuff, Vec3* pPositionBuff, Vec3* pVelocitiesBuff);




	public:
		// How will they know mass??
		ComputeUAVBuffer *neighbors;
		ComputeUAVBuffer *positions;
		ComputeUAVBuffer *velocities;
		ComputeUAVBuffer *densities;
		ComputeUAVBuffer *pressures;

	};


}


#endif