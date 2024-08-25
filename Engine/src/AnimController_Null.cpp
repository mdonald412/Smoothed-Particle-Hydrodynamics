//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "AnimController_Null.h"
#include "AnimController.h"

// User generated headers... 
#include "Null.Px.h"
#include "Null.Vx.h"

namespace Azul
{
	AnimController_Null::~AnimController_Null()
	{
	}

	AnimController_Null::AnimController_Null(AnimController_Null::Name _name)
		: AnimController(nullptr, AnimTime(AnimTime::Duration::FILM_24_FRAME))
	{
		this->name = _name;
	}

	void AnimController_Null::Update()
	{
	}

}

// --- End of File ---
