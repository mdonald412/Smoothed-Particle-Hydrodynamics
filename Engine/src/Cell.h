#ifndef CELL_H
#define CELL_H

#include "SPH_Spheres.h"
#include "MathEngine.h"
#include "GameObjectBasic.h"
#include "SPH_Stats.h"

#define MAX_SPHERES 100
#define SAMPLE_SIZE 32
#define MAX_NEIGHBORS 26

class Cell
{
public:
	struct Prism
	{
		Vec3 pos;
		float size = SMOOTH_RADIUS;
	};

	enum Type
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		MIDDLE
	};

	struct Orientation
	{
		bool Top;
		bool Bottom;
		bool Left;
		bool Right;
		bool Front;
		bool Back;
		bool Middle;
	};

	Cell();
	Cell& operator=(const Cell&) = default;
	Cell(const Cell&) = default;
	~Cell() = default;

	void Insert(SPH_Sphere* _sphere);
	void Clear();
	void Print();
	
private:
	void privInitCell();

public:
	void FixPointers(Vec3 index);
	std::vector<Cell*> vNeighbors;
	SPH_Sphere* spheres[MAX_SPHERES];
	int capacity;

	// Data for debugging...
	int index = 0;
	static Vec3 indexTrack;

	Prism proxyRect;
	GameObjectBasic* proxyGraphic;
	Orientation myOrient;

};


#endif