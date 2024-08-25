#ifndef GAME_OBJ_CUBE_H
#define GAME_OBJ_CUBE_H

#include "GameObjectBasic.h"
#include "GraphicsObject_ConstColorInstance.h"


namespace Azul
{
	class GameObjectCube : public GameObjectBasic
	{
	public:
		struct Prism
		{
			Vec3 pos;
			float cellUnit;
		};
		GameObjectCube(Vec3 lightColor, int instanceCount);

		static void Initialize(int instanceCount);

		// Big four
		GameObjectCube() = delete;
		GameObjectCube(const GameObjectCube&) = delete;
		GameObjectCube& operator=(GameObjectCube&) = delete;
		virtual ~GameObjectCube();

		virtual void Update(AnimTime currTime);
		void AddCube(Vec3 inPos, float cellUnit);

		std::vector<Prism*> myPrism;

	private:
		static GraphicsObject_ConstColorInstance* privGraphicsObject;

	};
}

#endif;