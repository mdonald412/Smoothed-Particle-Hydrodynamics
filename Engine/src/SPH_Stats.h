#ifndef SPH_STATS_H
#define SPH_STATS_H

#define SMOOTH_RADIUS 1.0f		 // Determines size of of smoother...
#define GRID_MAX 8              // Determines Resolution...
#define GRAVITY -50.0f		     // Gravity of environment...
#define RESTING_PRESSURE 20.0f	 // Pressure of fluid at rest...
#define RESTING_DENSITY 10.0f     // Pressure of fluid at rest...
#define NUM_SPHERES 1000
#define NUM_NEIGHBORS 32
#define CUBE_LENGTH 2
#define NUM_BOUNDARY_SPHERES 0
#define MAX_VELOCITY 100
#define FRAME_COUNT 500
#define INERTIA 0.9f


constexpr int MIN_ITERATIONS = 2; // Number of predictive corrective iterations...
constexpr float MAX_ERROR = 0.10f;   // Percent error acceptable for density....
constexpr float TIME_STEP = 0.04f;

// Timestep must satisfy the CFL condition of T <= 0.4 * (SPHERE_RADIUS/MAX_VELOCITY)

#endif