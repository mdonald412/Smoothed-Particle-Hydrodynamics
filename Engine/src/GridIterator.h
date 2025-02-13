//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef	GRID_ITERATOR_H
#define	GRID_ITERATOR_H

#include "Iterator.h"
#include "SPH_Spheres.h"
#include "Cell.h"

namespace Azul
{
	struct Neighborhood
	{
		SPH_Sphere* pSphere;
		std::vector<SPH_Sphere*> neighbors;
	};

	class GridIterator
	{
	public:

		
		GridIterator(Cell* pGrid, int size);

		Neighborhood Next();
		bool IsDone();
		Neighborhood First();
		Neighborhood Curr();

		void Reset();

	public:
		//void privClear();
		Cell* gridData;

		int iterCell;
		int iterSphere;


		int spheresPresented;
		int spheresTotal;


		Neighborhood current;


	public:
	};
}

#endif