#include "GameObjectSphere.h"
#include "GraphicsObject_ConstColorInstance.h"
#include "TexNodeMan.h"

GraphicsObject_FlatTextureInstance* Azul::GameObjectSphere::privGraphicsObject = nullptr;

Azul::GameObjectSphere::GameObjectSphere(Vec3 lightColor, int instanceCount)
	: GameObjectBasic(privGraphicsObject)
{
	//this->poGraphicsObject = nullptr;
	//*this->privGraphicsObject->poLightColor = Vec3(0, 0, 0);
}

void Azul::GameObjectSphere::Initialize(int instanceCount)
{
	if (privGraphicsObject == nullptr)
	{
		Vec3 color(1, 1, 1);
		TextureObject* brickTex = TexNodeMan::Find(TextureObject::Name::Brick);
		privGraphicsObject = new GraphicsObject_FlatTextureInstance(Mesh::Name::SPHERE, ShaderObject::Name::FlatTextureInstance, brickTex, instanceCount);
	}
}

Azul::GameObjectSphere::~GameObjectSphere()
{
	//delete myPrism;
	if (privGraphicsObject)
	{
		delete privGraphicsObject;
		poGraphicsObject = nullptr;
		privGraphicsObject = nullptr;
	}
}

void Azul::GameObjectSphere::Update(AnimTime currTime)
{
	int max = privGraphicsObject->instanceCount;
	int i = 0;
	while (i < max)
	{
		privGraphicsObject->pushWorld(*this->mySphere[i]->position, this->mySphere[i]->index);
		GameObjectBasic::protUpdate(currTime);
		i++;
	}
}

void Azul::GameObjectSphere::AddSphere(SPH_Sphere* inSphere)
{
	mySphere.push_back(inSphere);
	//inSphere->index = mySphere.size();
}
