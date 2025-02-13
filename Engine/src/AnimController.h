//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "AnimTime.h"

namespace Azul
{
	class Anim;
	class TimerController;

	class AnimController
	{
	public:
		enum Name
		{
			AnimController_01,
			AnimController_02,
			Null
		};

	public:
		AnimController(Anim *pAnim, AnimTime delta);
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void SetName(AnimController::Name inName);
		char* GetName();


		void Update();

	private:
		TimerController *poTimerControl;
		Anim *poAnim;

	public:
		AnimController::Name name;
	};
}

#endif

// --- End of File ---
