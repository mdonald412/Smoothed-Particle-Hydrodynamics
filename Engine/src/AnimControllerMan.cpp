//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#include "AnimControllerMan.h"
#include "AnimController_Null.h"
#include "ManBase.h"
#include "DLinkMan.h"

namespace Azul
{
	AnimControllerMan* AnimControllerMan::posInstance = nullptr;

	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
	AnimControllerMan::AnimControllerMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		// Preload the reserve
		this->proFillReservedPool(reserveNum);

		// initialize derived data here
		AnimController_Null* pAnimController = new AnimController_Null(AnimController::Name::Null);
		assert(pAnimController);
		
		this->poNodeCompare = new AnimObjectNode();
		assert(this->poNodeCompare);

		this->poNodeCompare->Set(pAnimController);
	}

	AnimControllerMan::~AnimControllerMan()
	{

		delete this->poNodeCompare;
		this->poNodeCompare = nullptr;

		// iterate through the list and delete
		Iterator* pIt = this->baseGetActiveIterator();

		DLink* pNode = pIt->First();

		// Walk through the nodes
		while (!pIt->IsDone())
		{
			AnimObjectNode* pDeleteMe = (AnimObjectNode*)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}

		pIt = this->baseGetReserveIterator();

		pNode = pIt->First();

		// Walk through the nodes
		while (!pIt->IsDone())
		{
			AnimObjectNode* pDeleteMe = (AnimObjectNode*)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	void AnimControllerMan::Create(int reserveNum, int reserveGrow)
	{
		// make sure values are ressonable 
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);

		// initialize the singleton here
		assert(posInstance == nullptr);

		// Do the initialization
		if (posInstance == nullptr)
		{
			posInstance = new AnimControllerMan(reserveNum, reserveGrow);
		}
	}

	void AnimControllerMan::Update()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		Iterator* pIt = pMan->baseGetActiveIterator();
		for (pIt->First(); !pIt->IsDone(); pIt->Next())
		{
			((AnimObjectNode*)pIt->Curr())->GetAnimObject()->Update();
		}
	}

	AnimController* AnimControllerMan::GetPlayControls()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
	
		return pMan->privPlayerController;
	}

	void AnimControllerMan::SetPlayerControls(AnimController* playerControls)
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();

		pMan->privPlayerController = playerControls;
	}

	void AnimControllerMan::Destroy()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete AnimControllerMan::posInstance;
		AnimControllerMan::posInstance = nullptr;
	}

	AnimObjectNode* AnimControllerMan::Add(AnimController* pAnimController) // Other stuff will be added here instead...
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();

		//assert(pMesh);
		AnimObjectNode* pNode = (AnimObjectNode*)pMan->baseAddToFront();
		assert(pNode != nullptr);

		// Initialize the date
		pNode->Set(pAnimController);
	//	pNode->SetName(inName);

		return pNode;
	}

	AnimController* AnimControllerMan::Find(AnimController::Name _name)
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan != nullptr);

		// Compare functions only compares two Nodes

		// So:  Use the Compare Node - as a reference
		//      use in the Compare() function
		AnimController* pAnimController = pMan->poNodeCompare->GetAnimObject();
		//assert(pShaderObject);

		pAnimController->name = _name;

		AnimObjectNode* pData = (AnimObjectNode*)pMan->baseFind(pMan->poNodeCompare);
		return pData->GetAnimObject();
	}

	void AnimControllerMan::Remove(AnimObjectNode* pNode)
	{
		assert(pNode != nullptr);

		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseRemove(pNode);
	}

	void AnimControllerMan::Dump()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
	AnimControllerMan* AnimControllerMan::privGetInstance()
	{
		// Safety - this forces users to call Create() first before using class
		assert(posInstance != nullptr);

		return posInstance;
	}

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
	DLink* AnimControllerMan::derivedCreateNode()
	{
		DLink* pNodeBase = new AnimObjectNode();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}

}

// --- End of File ---
