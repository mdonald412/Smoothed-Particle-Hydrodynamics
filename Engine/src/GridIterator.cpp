#include "GridIterator.h"
#include "GraphicsObject_ConstColor.h"

using namespace Azul;
#define GRID_SIZE 9;

GridIterator::GridIterator(Cell* pGrid, int size)
    : gridData(pGrid)
{
    iterCell = 0;
    iterSphere = 0;
    spheresPresented = 0;
    spheresTotal = size;
    current = Neighborhood();
}

//////////////////////////////////////////////////////////////////////////////
// THIS CODE IS REPEATED IN THE FIRST() METHOD... FIX EVENTUALLY /////////////
//////////////////////////////////////////////////////////////////////////////

Neighborhood GridIterator::Next()
{
    // Iterate
    iterSphere++;

    // Get the current cell that we're in
    Cell currCell = this->gridData[iterCell];

    int cellTotal = pow(GRID_MAX, 3);

    // Make sure we're not done with this cell, and if we are then iterate to next cell
    if (iterSphere >= currCell.capacity)
    {
        iterCell++;
        if (iterCell >= cellTotal)
        {
            spheresPresented++;
            //  assert(false);
            return Neighborhood(); // should never do this....
        }
        iterSphere = 0;
    }

    currCell = this->gridData[iterCell];

    while (currCell.capacity == 0)
    {
        if (iterCell >= cellTotal - 1)
        {
            spheresPresented++;
          //  assert(false);
            return Neighborhood(); // should never do this....
        }
        iterCell++;
        currCell = this->gridData[iterCell];
    }

    if (currCell.capacity == 2)
    {
       // Trace::out("Hello");
    }

    SPH_Sphere* currSphere = currCell.spheres[iterSphere];
    

    std::vector<SPH_Sphere*> neighbors;

    int i = 0;
    while (i < currCell.capacity)
    {
        if (i == iterSphere)
        {
            i++;
            continue; // the current sphere is not apart of the neighbors...
        }

        neighbors.push_back(currCell.spheres[i]);
        i++;
    }

    std::vector<Cell*> pNeighbors = currCell.vNeighbors;

    int j = 0;
    while (j < pNeighbors.size()) // This would indicate the end of the list...
    {
       // *((GraphicsObject_ConstColor*)pNeighbors[j]->proxyGraphic->GetGraphicsObject())->poLightColor = Vec3(0.75f, 0.0f, 0.75f);
        int k = 0;
        while (k < pNeighbors[j]->capacity)
        {
            if ((*currSphere->position - *pNeighbors[j]->spheres[k]->position).len() > SMOOTH_RADIUS)
            {
                k++;
                continue;
            }

            neighbors.push_back(pNeighbors[j]->spheres[k]); // Maybe store these as vectors so we can just append and be faster
            k++;
        }
        j++;
    }

    //if (currCell.myOrient.Left == true)
    //{
    //    // So this is on the bottom so we need to just add a temp sphere that is aligned to the bottom but in the same location as currSphere...
    //    // FOR NEXT
    //    SPH_Sphere* newSphere = new SPH_Sphere();
    //    newSphere->mass = 2.0f;
    //    *newSphere->PrePosition = Vec3(currSphere->position->x(), -4.0f, currSphere->position->z()); // Need to assign this to the bottom;;
    //    newSphere->radius = 0.05f;
    //    newSphere->type = SPH_Sphere::Type::Dynamic;

    //    neighbors.push_back(newSphere);
    //}
    //if (currCell.myOrient.Top == true)
    //{
    //    // So this is on the bottom so we need to just add a temp sphere that is aligned to the bottom but in the same location as currSphere...
    //    // FOR NEXT
    //    SPH_Sphere* newSphere = new SPH_Sphere();
    //    newSphere->mass = 2.0f;
    //    *newSphere->PrePosition = Vec3(currSphere->position->x(), -4.0f, currSphere->position->z()); // Need to assign this to the bottom;;
    //    newSphere->radius = 0.05f;
    //    newSphere->type = SPH_Sphere::Type::Dynamic;

    //    neighbors.push_back(newSphere);
    //}

    current = Neighborhood();
    current.neighbors = neighbors;
    current.pSphere = currSphere;
    spheresPresented++;

    return current;

}

bool Azul::GridIterator::IsDone()
{
   // return iterCell >= pow(GRID_MAX, 3) - 1;
    bool eval = false;

    if (this->spheresTotal == 0)
    {
        eval = true;
    }

    if (this->spheresPresented > spheresTotal)
    {
        eval = true;
    }

    return eval;
}

Neighborhood Azul::GridIterator::First()
{
    this->Reset();
    if (spheresTotal == 0)
    {
        return Neighborhood();
    }

    Cell* currCell = &gridData[iterCell];
    spheresPresented = 0;
  
    int i = 0;
    while (currCell->capacity == 0)
    {
        iterCell++;
        currCell = &gridData[iterCell];
    }

    SPH_Sphere* currSphere = currCell->spheres[iterSphere];

    std::vector<SPH_Sphere*> neighbors;

    i = 0;
    while (i < currCell->capacity)
    {
        if (i == iterSphere)
        {


            i++;
            continue; // the current sphere is not apart of the neighbors...
        }

        neighbors.push_back(currCell->spheres[i]);
        i++;
    }

    std::vector<Cell*> pNeighbors = currCell->vNeighbors; // SOMETHING GOING WRONG HERE

    int j = 0;
    while (j < pNeighbors.size()) // This would indicate the end of the list...
    {
        //*((GraphicsObject_ConstColor*)pNeighbors[j]->proxyGraphic->GetGraphicsObject())->poLightColor = Vec3(0.75f, 0.0f, 0.75f);
        int k = 0;
        while (k < pNeighbors[j]->capacity)
        {
            if ((*currSphere->position - *pNeighbors[j]->spheres[k]->position).len() > SMOOTH_RADIUS)
            {
                k++;
                continue;
            }

            neighbors.push_back(pNeighbors[j]->spheres[k]); // Maybe store these as vectors so we can just append and be faster maybeeee......
            k++;
          //  Trace::out("k: %d\n", k);
        }
        j++;
      //  Trace::out("j: %d\n", j);
    }

    //if (currCell->myOrient.Left == true)
    //{
    //    // So this is on the bottom so we need to just add a temp sphere that is aligned to the bottom but in the same location as currSphere...
    //    // FOR FIRST
    //    SPH_Sphere* newSphere = new SPH_Sphere();
    //    newSphere->mass = 2.0f;
    //    *newSphere->PrePosition = Vec3(currSphere->position->x(), -4.0f, currSphere->position->z()); // Need to assign this to the bottom;;
    //    newSphere->radius = 0.05f;
    //    newSphere->type = SPH_Sphere::Type::Dynamic;
   
    //    neighbors.push_back(newSphere);
    //}   
    //
    //if (currCell->myOrient.Top == true)
    //{
    //    // So this is on the bottom so we need to just add a temp sphere that is aligned to the bottom but in the same location as currSphere...
    //    // FOR NEXT
    //    SPH_Sphere* newSphere = new SPH_Sphere();
    //    newSphere->mass = 2.0f;
    //    *newSphere->PrePosition = Vec3(currSphere->position->x(), -4.0f, currSphere->position->z()); // Need to assign this to the bottom;;
    //    newSphere->radius = 0.05f;
    //    newSphere->type = SPH_Sphere::Type::Dynamic;

    //    neighbors.push_back(newSphere);
    //}

    Neighborhood returnHood = Neighborhood();
    returnHood.neighbors = neighbors;
    returnHood.pSphere = currSphere;
    this->current = returnHood;
    spheresPresented = 1;


    return returnHood;
}

Neighborhood Azul::GridIterator::Curr()
{
    // Need to reach into the cells of the grid data and return each sphere...
    return current;
}

void Azul::GridIterator::Reset()
{
    iterCell = 0;
    iterSphere = 0;
}
