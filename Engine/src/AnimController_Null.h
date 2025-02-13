//--------------------------------------------------------------

//--------------------------------------------------------------

#ifndef ANIM_CONTROLLER_NULL_H
#define ANIM_CONTROLLER_NULL_H

#include "AnimController.h"

namespace Azul
{
	class AnimController_Null : public AnimController
	{
	public:

	public:
		AnimController_Null() = delete;
		AnimController_Null(const AnimController_Null&) = delete;
		AnimController_Null& operator = (const AnimController_Null&) = delete;
		virtual ~AnimController_Null();

		AnimController_Null(AnimController_Null::Name _name);

		virtual void Update();

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------

	};
}

#endif

// --- End of File ---
