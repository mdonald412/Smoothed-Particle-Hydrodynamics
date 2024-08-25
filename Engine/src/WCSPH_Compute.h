#ifndef WCSPH_COMPUTE
#define WCSPH_COMPUTE

#include "ComputeUAVBuffer.h"
#include "ComputeCBVBuffer.h"
#include "ComputeRSVBuffer.h"
#include "SPH_Strategy.h"

namespace Azul
{
	class ComputeRSVBuffer;
	class ComputeUAVBuffer;
	class ComputeCBVBuffer;

	class WCSPH_Compute : public SPH_Strategy
	{
	public:
		WCSPH_Compute();
		WCSPH_Compute& operator=(WCSPH_Compute&) = default;
		WCSPH_Compute(WCSPH_Compute&) = default;
		~WCSPH_Compute();

		// Transfer data ... and provide buffers here I guess... although maybe I can call "Load" or something and have
		// it all written in here...

		//void Load(SPH_Sphere::NeighborID* pNeighborBuff, Vec3* pPositionBuff);
		//void DrawStage();

	public:
		static void initalize(int);

		// How will they know mass??
		static ComputeUAVBuffer *UAV_Neighbors;
		static ComputeUAVBuffer *UAV_Positions;
		static ComputeUAVBuffer *UAV_Velocities;
		static ComputeUAVBuffer *UAV_Densities;
		static ComputeUAVBuffer *UAV_Pressures;
		static ComputeRSVBuffer *RSV_Positions;

		static char* pBuffer;
		static SPH_Sphere::NeighborID* NeighborBuff;
		static Vec3* positionsBuff;

		static void solveParticles(std::vector<SPH_Sphere*>* myList);
		static void Load(SPH_Sphere::NeighborID* pNeighborBuff, Vec3* pPositionsBuff);



	};


}


#endif