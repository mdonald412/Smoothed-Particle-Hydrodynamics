#include "Cell.h"
#include <algorithm>

Cell::Cell()
	: capacity(0)
{
	this->vNeighbors.reserve(pow(GRID_MAX, 3));
	this->privInitCell();

	int i = 0;
	while (i < 100)
	{
		this->spheres[i] = nullptr;
		i++;
	}
}

void Cell::Insert(SPH_Sphere* _sphere)
{
	// Need to create a better check but this will be for debugging...
	assert(capacity < MAX_SPHERES);

	this->spheres[capacity] = _sphere;
	capacity++;
}

void Cell::Clear()
{
	int i = 0;
	while (i < capacity)
	{
		//Vec3 blueColor(0, 0, 0);
		Vec3 whiteColor(0, 1, 0);
		this->spheres[i]->color = whiteColor;
		this->spheres[i]->neighborsList->clear(); // Clears neighborlist...
		this->spheres[i] = nullptr;
		i++;
	}

	capacity = 0;
}

void Cell::Print()
{
	Trace::out("\n");
	Trace::out("CELL #%d\n", index);
	Trace::out("	NEIGHBORS: \n", index);
	for (int i = 0; i < vNeighbors.size(); i++)
	{
		Trace::out("		Neighbor %d is index %d\n", i, vNeighbors[i]->index);
	}
	Trace::out("\n");
}

void Cell::privInitCell()
{
	int transformations[26];

	int shiftUp = pow(GRID_MAX, 2);
	int shiftRight = GRID_MAX;
	int shiftForward = 1;
	int shiftDown = -shiftUp;
	int shiftLeft = -shiftRight;
	int shiftBackward = -shiftForward;

	// Top....
	transformations[0] = shiftUp;
	transformations[1] = shiftUp + shiftRight;  // Right
	transformations[2] = shiftUp + shiftLeft;   // Left
	transformations[3] = shiftUp + shiftForward;// Forward
	transformations[4] = shiftUp + shiftBackward;// Backward
	transformations[5] = shiftUp + shiftRight + shiftForward; // Right & forward
	transformations[6] = shiftUp + shiftLeft + shiftForward;  // left & forward
	transformations[7] = shiftUp + shiftRight + shiftBackward; // right & backward
	transformations[8] = shiftUp + shiftLeft + shiftBackward; // left & backward

	// Bottom....
	transformations[9] = shiftDown;
	transformations[10] = shiftDown + shiftRight; // right
	transformations[11] = shiftDown + shiftLeft; // left
	transformations[12] = shiftDown + shiftForward; // forward
	transformations[13] = shiftDown + shiftBackward; // backward
	transformations[14] = shiftDown + shiftRight + shiftForward; // right & forward
	transformations[15] = shiftDown + shiftLeft + shiftForward; // left & forward
	transformations[16] = shiftDown + shiftRight + shiftBackward; // right & backward
	transformations[17] = shiftDown + shiftLeft + shiftBackward; // left & backward

	transformations[18] = shiftLeft; // left
	transformations[19] = shiftRight; // right
	transformations[20] = shiftForward; // forward
	transformations[21] = shiftBackward; // backward
	transformations[22] = shiftLeft + shiftForward; // left & forward
	transformations[23] = shiftRight + shiftForward; // right & forward
	transformations[24] = shiftLeft + shiftBackward; // left & backward
	transformations[25] = shiftRight + shiftBackward; // right & backward


	this->vNeighbors.push_back(this + transformations[0]);
	this->vNeighbors.push_back(this + transformations[1]);
	this->vNeighbors.push_back(this + transformations[2]);
	this->vNeighbors.push_back(this + transformations[3]);
	this->vNeighbors.push_back(this + transformations[4]);
	this->vNeighbors.push_back(this + transformations[5]);
	this->vNeighbors.push_back(this + transformations[6]);
	this->vNeighbors.push_back(this + transformations[7]);
	this->vNeighbors.push_back(this + transformations[8]);
	this->vNeighbors.push_back(this + transformations[9]);
	this->vNeighbors.push_back(this + transformations[10]);
	this->vNeighbors.push_back(this + transformations[11]);
	this->vNeighbors.push_back(this + transformations[12]);
	this->vNeighbors.push_back(this + transformations[13]);
	this->vNeighbors.push_back(this + transformations[14]);
	this->vNeighbors.push_back(this + transformations[15]);
	this->vNeighbors.push_back(this + transformations[16]);
	this->vNeighbors.push_back(this + transformations[17]);
	this->vNeighbors.push_back(this + transformations[18]);
	this->vNeighbors.push_back(this + transformations[19]);
	this->vNeighbors.push_back(this + transformations[20]);
	this->vNeighbors.push_back(this + transformations[21]);
	this->vNeighbors.push_back(this + transformations[22]);
	this->vNeighbors.push_back(this + transformations[23]);
	this->vNeighbors.push_back(this + transformations[24]);
	this->vNeighbors.push_back(this + transformations[25]);
}

void Cell::FixPointers(Vec3 index)
{
	std::vector<int> removeList;

	if (((int)index.x()) == (GRID_MAX - 1))
	{
		// removeFront();
		myOrient.Front = true;
		Trace::out("Front Removed\n\n");
		removeList.push_back(23);
		removeList.push_back(22);
		removeList.push_back(20);
		removeList.push_back(15);
		removeList.push_back(14);
		removeList.push_back(12);
		removeList.push_back(6);
		removeList.push_back(5);
		removeList.push_back(3);

	}

	if (((int)index.x()) == 0)
	{
		// Remove back...
		myOrient.Back = true;

		Trace::out("Back Removed\n\n");
		removeList.push_back(25);
		removeList.push_back(24);
		removeList.push_back(21);
		removeList.push_back(17);
		removeList.push_back(16);
		removeList.push_back(13);
		removeList.push_back(8);
		removeList.push_back(7);
		removeList.push_back(4);
	}

	if (((int)index.z()) == (GRID_MAX - 1))
	{
		// remove top
		Trace::out("Top Removed\n\n");
		myOrient.Top = true;

		//myType = Type::BOTTOM;
		removeList.push_back(8);
		removeList.push_back(7);
		removeList.push_back(6);
		removeList.push_back(5);
		removeList.push_back(4);
		removeList.push_back(3);
		removeList.push_back(2);
		removeList.push_back(1);
		removeList.push_back(0);
	}

	if (((int)index.z()) == 0)
	{
		// remove bottom
		Trace::out("Bottom Removed\n\n");
		myOrient.Bottom = true;

		//myType = Type::BOTTOM;
		removeList.push_back(17);
		removeList.push_back(16);
		removeList.push_back(15);
		removeList.push_back(14);
		removeList.push_back(13);
		removeList.push_back(12);
		removeList.push_back(11);
		removeList.push_back(10);
		removeList.push_back(9);

		
	}


	if (((int)index.y()) == 0)
	{
		// remove left
		Trace::out("Left Removed\n\n");
		myOrient.Left = true;

		removeList.push_back(24);
		removeList.push_back(22);
		removeList.push_back(18);
		removeList.push_back(17);
		removeList.push_back(15);
		removeList.push_back(11);
		removeList.push_back(8);
		removeList.push_back(6);
		removeList.push_back(2);
	}

	if (((int)index.y()) == (GRID_MAX - 1))
	{
		// remove right
		Trace::out("Right Removed\n\n");
		myOrient.Right = true;

		removeList.push_back(25);
		removeList.push_back(23);
		removeList.push_back(19);
		removeList.push_back(16);
		removeList.push_back(14);
		removeList.push_back(10);
		removeList.push_back(7);
		removeList.push_back(5);
		removeList.push_back(1);
	}

	std::sort(removeList.begin(), removeList.end());
	auto iter = std::unique(removeList.begin(), removeList.end());
	removeList.erase(iter, removeList.end());

	int removeCapacity = removeList.size() - 1;
	for (int j = removeCapacity; j >= 0; j--)
	{
		this->vNeighbors.erase(this->vNeighbors.begin() + removeList[j]);
	}

	this->Print();
}


