//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"

namespace Azul
{

	class GameObject : public PCSNode
	{
	public:
		GameObject(GraphicsObject *graphicsObject);

		// Big four
		GameObject() = delete;
		GameObject(const GameObject &) = delete;
		GameObject &operator = (const GameObject &) = delete;
		virtual ~GameObject();

		virtual void Draw();
		virtual void Update(AnimTime currTime) = 0;

		// Set / Get:
		GraphicsObject *GetGraphicsObject();
		Mat4 *GetWorld();

		void SetWorld(Mat4 *pWorld);

		void DrawEnable();
		void DrawDisable();

	protected:
		Mat4 *poWorld;

	protected:
		GraphicsObject *poGraphicsObject;
		bool mDrawEnable;

	};
}

#endif


// --- End of File ---
