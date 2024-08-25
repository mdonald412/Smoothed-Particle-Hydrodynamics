#include "Grid.h"
#include "MathEngine.h"
#include "GraphicsObject_ConstColor.h"
#include "ShaderObjectNodeMan.h"
#include "GameObjectMan.h"
#include "GameObjectCube.h"
#include "MeshProto.h"
#include <algorithm>

#define MARGIN 0.001f

Grid::Grid()
	: capacity(0),
	gridData(new Cell[pow(GRID_MAX, 3)]()),
	pIterator(new GridIterator(this->gridData, pow(GRID_MAX, 3)))
{
	this->SetConnections();
	this->anchorPoint = Vec3(0.0f, 0.0f, 0.0f);
}

Grid::~Grid()
{
	delete[] gridData;
	delete pIterator;
}

void Grid::Insert(SPH_Sphere* _sphere)
{
	if (!Bounded(*_sphere->position))
	{
		//assert(false);
	}
	Vec3 Transform1 = Vec3(((float)GRID_MAX*SMOOTH_RADIUS) / 2, ((float)GRID_MAX*SMOOTH_RADIUS) / 2, ((float)GRID_MAX*SMOOTH_RADIUS) / 2);
	Vec3 corrected = *_sphere->position + Transform1 - anchorPoint; // This corrected should depend on our origin...
	float multiply = 1.0f/SMOOTH_RADIUS;
	corrected *= multiply;
	int hashedIndex = Hash(corrected);
	
	this->gridData[hashedIndex].Insert(_sphere);
	capacity++;
}

void Grid::Clear()
{
	int i = 0;
	int maxSpheres = pow(GRID_MAX, 3);
	while (i < maxSpheres)
	{
		this->gridData[i].Clear();
		i++;
	}

	capacity = 0;
}

GridIterator* Grid::getIterator()
{
	this->pIterator->spheresTotal = this->capacity;
	return this->pIterator;
}

bool Grid::BoundedX(SPH_Sphere* inSphere)
{
	Vec3& inVec = *inSphere->position;
	Vec3& inVelocity = *inSphere->Velocity;
	bool returnVal = true;
	float addVal = ((float)(GRID_MAX * SMOOTH_RADIUS) / 2);

	if (inVec.x() < (anchorPoint.x() - addVal + MARGIN))
	{
		float transform = anchorPoint.x() - addVal - inVec.x() + MARGIN;
		inVec[x] += transform;
		returnVal = false;
	}

	if (inVec.x() > (anchorPoint.x() + addVal - MARGIN))
	{
		float transform = anchorPoint.x() + addVal - inVec.x() - MARGIN;
		inVec[x] += transform;
		returnVal = false;
	}

	return returnVal;
}


bool Grid::BoundedY(SPH_Sphere* inSphere)
{
	Vec3& inVec = *inSphere->position;
	Vec3& inVelocity = *inSphere->Velocity;
	bool returnVal = true;
	float addVal = ((float)(GRID_MAX * SMOOTH_RADIUS) / 2);

	if (inVec.y() < (anchorPoint.y() - addVal + MARGIN))
	{
		float transform = anchorPoint.y() - addVal - inVec.y() + MARGIN;
		inVec[y] += transform;
		returnVal = false;
	}

	if (inVec.y() > (anchorPoint.y() + addVal - MARGIN))
	{
		float transform = anchorPoint.y() + addVal - inVec.y() - MARGIN;
		inVec[y] += transform;
		returnVal = false;
	}

	return returnVal;
}


bool Grid::BoundedZ(SPH_Sphere* inSphere)
{
	Vec3& inVec = *inSphere->position;
	Vec3& inVelocity = *inSphere->Velocity;
	bool returnVal = true;
	float addVal = ((float)(GRID_MAX * SMOOTH_RADIUS) / 2);

	if (inVec.z() < (anchorPoint.z() - addVal + MARGIN))
	{
		float transform = anchorPoint.z() - addVal - inVec.z() + MARGIN;
		inVec[z] += transform;
		returnVal = false;
	}

	if (inVec.z() > (anchorPoint.z() + addVal - MARGIN))
	{
		float transform = anchorPoint.z() + addVal - inVec.z() - MARGIN;
		inVec[z] += transform;
		returnVal = false;
	}
	
	return returnVal;
}


bool Grid::Bounded(Vec3 inVec)
{
	bool returnVal = true;
	float addVal = ((float)(GRID_MAX * SMOOTH_RADIUS) / 2);

	if (inVec.x() < anchorPoint.x() - addVal)
	{
		returnVal = false;
	}

	if (inVec.x() > anchorPoint.x() + addVal)
	{
		returnVal = false;
	}

	if (inVec.y() < anchorPoint.y() - addVal)
	{
		returnVal = false;
	}

	if (inVec.y() > anchorPoint.y() + addVal)
	{
		returnVal = false;
	}

	if (inVec.z() < anchorPoint.z() - addVal)
	{
		returnVal = false;
	}

	if (inVec.z() > anchorPoint.z() + addVal)
	{
		returnVal = false;
	}
	
	return returnVal;
}

Vec3 Grid::GetAnchorPoint()
{
	return anchorPoint;
}

int Grid::Hash(Vec3 pos)
{	// So we need to round each of these down to the nearest Cell unit and then add them.

	int convertedX = (int)(pos.x());// *((GRID_MAX / 2) * SMOOTH_RADIUS)) / SMOOTH_RADIUS); //+ (GRID_MAX / 2) - 1; // <--- Using cast for rounding at this point...
	int convertedY = (int)(pos.y());// *((GRID_MAX / 2) * SMOOTH_RADIUS)) / SMOOTH_RADIUS); //+ (GRID_MAX / 2) - 1; // <--- Using cast for rounding at this point...
	int convertedZ = (int)(pos.z());// *((GRID_MAX / 2) * SMOOTH_RADIUS)) / SMOOTH_RADIUS); //+ (GRID_MAX/2) - 1; // <--- Using cast for rounding at this point...

	int returnMe = (convertedX + (convertedY * GRID_MAX) + (convertedZ * pow(GRID_MAX, 2)));
	return returnMe;
}


// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------- GARBAGE // DO NOT TOUCH ----------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

void Grid::SetConnections()
{
	// I think maybe we should set pointers in here just to make things faster during runtime
	// So for each cell connect it to it's neighbors as a basically a list of pointers.

	int arraySize = pow(GRID_MAX, 3);

	int i = 0;
	while (i < arraySize)
	{
		this->gridData[i].index = i;
		i++;
	}

	//GameObjectCube::Initialize(arraySize);
	Vec3 white(1, 1, 1);
	//this->proxyGraphic = new GameObjectCube(white, arraySize);

	for (int i = 0; i < GRID_MAX; i++)
	{
		for (int j = 0; j < GRID_MAX; j++)
		{
			for (int k = 0; k < GRID_MAX; k++)
			{
				// EVENTUALLY PUSH THIS ALL TO CELL ON INITIALIZATION...
				// CAN PASS IN INDEX AND IT WILL DO ALL THIS WORK...

				Vec3 index(k, j, i);
				int hashedIndex = Grid::Hash(index);

				Cell* currCell = &this->gridData[hashedIndex];
				currCell->FixPointers(index);

				// The following is all setup for the graphic proxy...
				Vec3 corrected = (index - Vec3(((float)GRID_MAX) / 2, ((float)GRID_MAX) / 2, ((float)GRID_MAX) / 2) - anchorPoint) * SMOOTH_RADIUS; // This corrected should depend on our origin...
				Vec3 lightColor(0.0f, 0.0f, 1.0f);

				//currCell->proxyGraphic = new GameObjectCube(lightColor, corrected, SMOOTH_RADIUS);
				//((GameObjectCube*)this->proxyGraphic)->AddCube(corrected, SMOOTH_RADIUS);
			}
		}
	}

	//GameObjectMan::Add(this->proxyGraphic, GameObjectMan::GetRoot());

}

	

	// In order for this to work we need to make the grid an array of linked lists
	// rather than array of arrays. We need some sphere noooooodes :)))




