#ifndef SPH_STRATEGY
#define SPH_STRATEGY

#include "SPH_Spheres.h"
#include "SPH_Scene.h"

class SPH_Strategy
{
public:
	enum Strategy
	{
		CPU,
		GPU,
		CACHED
	}; 

protected:
	static void initialize(int);
	static void RecordFrame(Vec3* pBuff);



	//static void solveParticles(std::vector<SPH_Sphere*>* inList);

	static Strategy myType;
	static SPH_Scene* myScene; // oh boyyy this is a big bad static TRAP!!!
	
public:
	static void Destroy();
	static void solveParticles(std::vector<SPH_Sphere*>* inList);

	static int frame;
	static void Write();
	static void Read();

private:
	static bool cached;


};

#endif
