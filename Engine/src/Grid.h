#ifndef GRID_H
#define GRID_H

#include "SPH_Spheres.h"
#include "Cell.h"
#include "GridIterator.h"

//#define GRID_MAX 5
class Grid
{
public:

	enum position
	{
		

	};

	// public methods
	Grid();
	Grid& operator=(const Grid&) = delete;
	Grid(const Grid&) = delete;
	~Grid();

	void Insert(SPH_Sphere* _sphere);
	void Clear();
	GridIterator* getIterator();
	bool BoundedX(SPH_Sphere* inSphere);
	bool BoundedY(SPH_Sphere* inSphere);
	bool BoundedZ(SPH_Sphere* inSphere);
	bool Bounded(Vec3);

	Vec3 GetAnchorPoint();

public:
	// public data
	Vec3 origin;

private:
	// private methods
	void SetConnections();
	static int Hash(Vec3);

private:
	// private data
	Cell* gridData;
	int capacity;
	GridIterator* pIterator;
	Vec3 anchorPoint;
	GameObject* proxyGraphic;
	
};

#endif GRID_H