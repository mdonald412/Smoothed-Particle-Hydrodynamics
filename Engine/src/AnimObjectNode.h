//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef ANIM_OBJECT_NODE_H
#define ANIM_OBJECT_NODE_H

#include "DLink.h"
#include "AnimController.h"

namespace Azul
{
	class AnimObjectNode : public DLink
	{
	public:
		AnimObjectNode();
		AnimObjectNode(const AnimController&) = delete;
		AnimObjectNode& operator = (const AnimController&) = delete;
		virtual ~AnimObjectNode();

		void Set(AnimController* pAnimObject);
		void SetName(AnimController::Name inName);
		//AnimController::Name GetName();
		AnimController* GetAnimObject();

		virtual char* GetName() override;
		virtual void Wash() override;
		virtual bool Compare(DLink* pTargetNode) override;
		virtual void Dump() override;

	private:
		void privClear();

		//--------------------------------------------------
		// Data
		//--------------------------------------------------
		AnimController* poAnim;
		AnimController::Name pName;
	};
}

#endif

// --- End of File ---
