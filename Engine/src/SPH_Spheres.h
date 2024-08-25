#ifndef SPH_SPHERES_H
#define SPH_SPHERES_H

#include "MathEngine.h"

using namespace Azul;

//static float xOffset = 0.0f;

#define SPHERE_RADIUS 0.25f
#define SPHERE_MASS 10.0f;

#include "GameObject.h"
#include "GameObjectMan.h"


class SPH_Sphere
{
public:
	typedef int NeighborID;

public:
	enum Type
	{
		Active,
		Static,
		Dynamic
	};

public:
	SPH_Sphere();
	SPH_Sphere(const SPH_Sphere&) = default;
	SPH_Sphere& operator= (const SPH_Sphere&) = default;
	~SPH_Sphere();

	
	Vec3* position; // Essential
	Vec3* PrePosition; // Essential
	Vec3* Velocity; // Essential
	Vec3* PreVelocity; // Essential
	Vec3* Viscosity; // Essential?
	Vec3* PressureForce; // Essential
	Vec3* NonPressureForces; // Essential?

	float radius; // Not essential... is stored in stats
	float mass;   // Not essential... is stored in stats
	int index;    // Good for debugging...

	Vec3 color; // Useless for now...
	
	SPH_Sphere::Type type; // Essential

	std::vector<SPH_Sphere*>* neighborsList; // Essential...

	// For solver...
	float pressure;
	float density;
	float PreDensity;

private:
	static int indexCount;
};

#endif