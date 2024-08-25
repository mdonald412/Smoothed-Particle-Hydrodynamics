//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectRigid.h"
#include "GraphicsObject.h"

namespace Azul
{

	GameObjectRigid::GameObjectRigid(GraphicsObject *pGraphicsObject)
		: GameObject(pGraphicsObject)
	{

	}

	void GameObjectRigid::Update(AnimTime currentTime)
	{

	}

	GameObjectRigid::~GameObjectRigid()
	{
		if (poGraphicsObject)
		{
			delete poGraphicsObject;
			poGraphicsObject = nullptr;
		}
	//	poGraphicsObject = nullptr;
	}

}

// --- End of File ---
