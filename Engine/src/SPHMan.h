#ifndef SPH_MAN_H
#define SPH_MAN_H

#include "Grid.h"
#include "SPH_Spheres.h"
#include "GameObjectSphere.h"
#include "WCSPH_Compute.h"

namespace Azul
{
	class SPHMan
	{
	public:
		SPHMan(const SPHMan&) = delete;
		SPHMan& operator =(const SPHMan&) = delete;

		static void Create();
		static void Destroy();
		static void Update(AnimTime);
		static Grid* GetSpheresGrid();
		static std::vector<SPH_Sphere*> GetSpheresList();
		static SPH_Sphere* AddSphere(float mass, Vec3 position, float radius, SPH_Sphere::Type = SPH_Sphere::Type::Active);
		

		//static void AddObject(GameObjectRigidPhysics*);
		
	private:
		SPHMan();
		~SPHMan();

		static void FillNeighborhood();
		static void FixPositions();

		static SPHMan* posInstance;
		static SPHMan* privGetInstance();
		GameObjectSphere* pGameObj;

		WCSPH_Compute* computeSolver;
		                                     
		std::vector<SPH_Sphere*> spheresList; // <--- Shared data between these two objects. They share the spheres. Later down the line see if this is necessary or not.					  ...
	
	public:
		Grid* spheresGrid;
		ID3D11Buffer* pPositionsGPU_Out;

		SPH_Sphere::NeighborID* NeighborBuff;
		Vec3* positionsBuff;

	};
}

#endif