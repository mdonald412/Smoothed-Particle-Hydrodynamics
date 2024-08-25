#include "SPH_Spheres.h"
#include "SPH_Stats.h"

int SPH_Sphere::indexCount = 0;

SPH_Sphere::SPH_Sphere()
    : position(new Vec3(0.0f, 0.0f, 0.0f)),
    PrePosition(new Vec3(0.0f, 0.0f, 0.0f)),
    Velocity(new Vec3(0.0f, 0.0f, 0.0f)),
    PreVelocity(new Vec3(0.0f, 0.0f, 0.0f)),
    Viscosity(new Vec3(0.0f, 0.0f, 0.0f)),
    PressureForce(new Vec3()),
    NonPressureForces(new Vec3()),
    radius(SPHERE_RADIUS),
    color(Vec3(1.0f, 1.0f, 1.0f)),
    pressure(RESTING_PRESSURE),
    density(0.0f),
    PreDensity(0.0f),
      neighborsList(new std::vector<SPH_Sphere*>)
{
	mass = SPHERE_MASS;
}

SPH_Sphere::~SPH_Sphere()
{
    delete position;
    delete Velocity;
    delete Viscosity;
    delete PressureForce;
    delete NonPressureForces;
    delete neighborsList;
    delete PrePosition;
    delete PreVelocity;
}