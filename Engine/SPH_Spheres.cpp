#include "SPH_Spheres.h"

SPH_Sphere::

AzuL:SPH_Sphere::SPH_Sphere()
{
	index = indexCount++;
	position = Vec3(0.0f, 0.0f, 0.0f);
	Velocity = Vec3(0.0f, 0.0f, 0.0f);
	radius = SPHERE_RADIUS;
	mass = SPHERE_MASS;
	color = Vec3(1.0f, 1.0f, 1.0f);
}