//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "TimerController.h"
#include "Anim.h"
#include "StringThis.h"

namespace Azul
{
	AnimController::AnimController(Anim* pAnim, AnimTime delta)
		: poTimerControl(nullptr)
	{
		// Animation object
		this->poAnim = pAnim;

		// TimerController
		if (poAnim)
		{
			AnimTime maxTime = poAnim->FindMaxTime();
			AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
			this->poTimerControl = new TimerController(delta, minTime, maxTime);
		}

	}

	AnimController::~AnimController()
	{
		// Safe delete for now....
		if (this->poAnim)
		{
			delete poAnim;
		}
		if (this->poTimerControl)
		{
			delete poTimerControl;
		}
	}

	void AnimController::SetName(AnimController::Name inName)
	{
		this->name = inName;
	}

	char* AnimController::GetName()
	{
		return StringThis(this->name);
	}

	void AnimController::Update()
	{
		this->poTimerControl->Update();

		// interpolate all bones
		this->poAnim->Animate(this->poTimerControl->GetCurrTime());

	}
}

// --- End of File ---
