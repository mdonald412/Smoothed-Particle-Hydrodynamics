#ifndef SPH_SCENE_H
#define SPH_SCENE_H

#include "MathEngine.h"
#include "SPH_Frame.h"
#include "SPH_Scene.pb.h"

namespace Azul
{
	class SPH_Scene
	{
	public:
		SPH_Scene();
		SPH_Scene(int, int);
		~SPH_Scene();
		SPH_Scene(SPH_Scene&) = delete;
		SPH_Scene& operator=(SPH_Scene&) = delete;

		void HandleFrame(Vec3* positions, int frameCount);

		void Serialize(SPH_Scene_proto& out) const;
		void Deserialize(const SPH_Scene_proto& in);

		int count;
		SPH_Frame* Frames;
	};
}

#endif