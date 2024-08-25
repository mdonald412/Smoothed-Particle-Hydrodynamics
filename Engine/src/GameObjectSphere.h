#ifndef GAME_OBJ_Sphere_H
#define GAME_OBJ_Sphere_H

#include "GameObjectBasic.h"
#include "GraphicsObject.h"
#include "SPH_Spheres.h"
#include "GraphicsObject_FlatTextureInstance.h"

namespace Azul
{
	class GameObjectSphere : public GameObjectBasic
	{
	public:

		GameObjectSphere(Vec3 lightColor, int instanceCount);

		static void Initialize(int instanceCount);

		// Big four
		GameObjectSphere() = delete;
		GameObjectSphere(const GameObjectSphere&) = delete;
		GameObjectSphere& operator=(GameObjectSphere&) = delete;
		virtual ~GameObjectSphere();

		virtual void Update(AnimTime currTime);
		void AddSphere(SPH_Sphere* inSphere);

	public:
		std::vector<SPH_Sphere*> mySphere;

	private:
		static GraphicsObject_FlatTextureInstance* privGraphicsObject;

	};
}

#endif;