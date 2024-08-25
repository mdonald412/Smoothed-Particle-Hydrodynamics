#ifndef ANIM_CONTROLLER_MAN_H
#define ANIM_CONTROLLER_MAN_H

#include "ManBase.h"
#include "AnimController.h"
#include "AnimObjectNode.h"

namespace Azul
{
	class AnimControllerMan : public ManBase
	{
	private:
		static AnimControllerMan* privGetInstance();


		AnimControllerMan() = delete;
		AnimControllerMan(const AnimControllerMan&) = delete;
		AnimControllerMan& operator = (const AnimControllerMan&) = delete;
		~AnimControllerMan();

		AnimControllerMan(int reserveNum, int reserveGrow);

		//----------------------------------------------------------------------
		// Override Abstract methods
		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
		// Static Methods
		//----------------------------------------------------------------------
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		static AnimObjectNode* Add(AnimController* pAnimController);
		static AnimController* Find(AnimController::Name name);

		static void Remove(AnimObjectNode* pNode);
		static void Dump();

		static void Update();
		static AnimController* GetPlayControls();
		static void SetPlayerControls(AnimController*);


		//----------------------------------------------------------------------
		// Private methods
		//----------------------------------------------------------------------
	protected:
		DLink* derivedCreateNode() override;

		//----------------------------------------------------------------------
		// Data: unique data for this manager 
		//----------------------------------------------------------------------
	private:
		AnimObjectNode* poNodeCompare;
		static AnimControllerMan* posInstance;

		AnimController* privPlayerController;

	};
}

#endif ANIM_MAN_H