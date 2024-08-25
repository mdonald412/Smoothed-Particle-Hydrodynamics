#ifndef SPH_FRAME
#define SPH_FRAME

#include "Vec3Data.h"
#include "Vec3Data.pb.h"
#include "SPH_Frame.pb.h"

namespace Azul
{
	class SPH_Frame
	{
	public:
		SPH_Frame();
		~SPH_Frame();
		SPH_Frame(SPH_Frame&) = default;
		SPH_Frame& operator=(SPH_Frame&) = default;

		void PackFrame(Vec3* framePositions);

		void Serialize(SPH_Frame_proto& out) const;
		void Deserialize(const SPH_Frame_proto& in);


	public:
		int count;
		Vec3Data* FramePositions;
	};
}

#endif