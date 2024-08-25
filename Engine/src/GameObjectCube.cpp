#include "GameObjectCube.h"
#include "GraphicsObject_ConstColorInstance.h"
#include "Cell.h"
#include "TexNodeMan.h"

Azul::GraphicsObject_ConstColorInstance* Azul::GameObjectCube::privGraphicsObject = nullptr;

Azul::GameObjectCube::GameObjectCube(Vec3 lightColor, int instanceCount)
	: GameObjectBasic(privGraphicsObject)
{
	GameObjectBasic::SetScale(SMOOTH_RADIUS, SMOOTH_RADIUS, SMOOTH_RADIUS);
	GameObjectBasic::Update(AnimTime(AnimTime::Duration::ONE_SECOND));
}

void Azul::GameObjectCube::Initialize(int instanceCount)
{
	if (privGraphicsObject == nullptr)
	{
		Vec3 color(1, 1, 1);
		privGraphicsObject = new GraphicsObject_ConstColorInstance(Mesh::Name::CUBE, ShaderObject::Name::ConstColorInstance, color, instanceCount);
	}
}

Azul::GameObjectCube::~GameObjectCube()
{
	if (privGraphicsObject)
	{
		int i = 0;
		while (i < this->privGraphicsObject->instanceCount)
		{
			delete this->myPrism[i];
			i++;
		}

		delete privGraphicsObject;
		privGraphicsObject = nullptr;
	}
}

void Azul::GameObjectCube::Update(AnimTime currTime)
{
	int max = privGraphicsObject->instanceCount;
	int i = 0;
	while (i < max)
	{
		//Mat4 inWorld = this->privGraphicsObject->GetWorld() + Trans(this->myPrism[i]->pos);
		Mat4 inWorld = this->privGraphicsObject->GetWorld() * Trans(this->myPrism[i]->pos);
		//myCube[i]->position += mySphere[i]->Velocity;
		privGraphicsObject->pushWorld(inWorld.T(), i);
		//privGraphicsObject->pushWorld(Trans(this->myPrism[i]->pos), i);
		GameObjectBasic::protUpdate(currTime);
		i++;
	}
}


void Azul::GameObjectCube::AddCube(Vec3 inPos, float cellUnit)
{
	Prism* newPrism = new Prism();
	newPrism->pos = inPos;
	newPrism->cellUnit = cellUnit;
	myPrism.push_back(newPrism);
}
