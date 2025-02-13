//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#include "AnimObjectNode.h"
#include "StringThis.h"
#include "AnimController_Null.h"

namespace Azul
{
    AnimObjectNode::AnimObjectNode()
        : DLink(),
        poAnim(nullptr)
    {
        this->privClear();
    }

    AnimObjectNode::~AnimObjectNode()
    {
        this->privClear();
    }

    void AnimObjectNode::Set(AnimController* pAnimObject)
    {
        this->poAnim = pAnimObject;
    }

    void AnimObjectNode::SetName(AnimController::Name inName)
    {
        this->poAnim->SetName(inName);
    }

    AnimController* AnimObjectNode::GetAnimObject()
    {
        return this->poAnim;
    }

    void AnimObjectNode::privClear()
    {
       if (this->poAnim)
       {

          if (this->poAnim->name == AnimController::Name::Null)
          {
              delete (AnimController_Null*)this->poAnim;
          }
          else
          {
              delete this->poAnim;
          }
       }
        
        this->poAnim = nullptr;
    }

    char* AnimObjectNode::GetName()
    {
        char* pName = nullptr;
        if (this->poAnim)
        {
            pName = this->poAnim->GetName();
        }

        return pName;
    }

    void AnimObjectNode::Wash()
    {
        this->privClear();
    }

    bool AnimObjectNode::Compare(DLink* pTargetNode)
    {
        // This is used in ManBase.Find() 
        assert(pTargetNode);

        AnimObjectNode* pDataB = (AnimObjectNode*)pTargetNode;

        bool status = false;

       

        if (this->poAnim->name == pDataB->poAnim->name)
        {
            status = true;
        }

        return status;
    }

    void AnimObjectNode::Dump()
    {
        Trace::out("      ShaderObjectNode(%p)\n", this);

        // Data:
        if (this->poAnim)
        {
            Trace::out("      ShaderObject(%p) \n", this->poAnim);
            Trace::out("      Name: %s \n", StringMe(this->poAnim->name));
        }
        else
        {
            Trace::out("      Name: %s \n", "null");
        }

        DLink::Dump();
    }
}

// --- End of File ---
