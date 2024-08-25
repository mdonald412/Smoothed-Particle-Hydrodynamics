#include "SPH_Frame.h"

Azul::SPH_Frame::SPH_Frame()
{
}

Azul::SPH_Frame::~SPH_Frame()
{
	delete[] this->FramePositions;
}

void Azul::SPH_Frame::PackFrame(Vec3* framePositions)
{
	int i = 0;
	while (i < count)
	{
		this->FramePositions[i].x = framePositions[i].x();
		this->FramePositions[i].y = framePositions[i].y();
		this->FramePositions[i].z = framePositions[i].z();
		i++;
	}
}

void Azul::SPH_Frame::Serialize(SPH_Frame_proto& out) const
{
	out.set_count(count);
	int i = 0;
	while (i < count)
	{
		Vec3Data_proto tmpVec3_proto;
		this->FramePositions[i].Serialize(tmpVec3_proto);
		*out.add_framepositions() = tmpVec3_proto;
		i++;
	}
}

void Azul::SPH_Frame::Deserialize(const SPH_Frame_proto& in)
{
	this->count = in.count();

	this->FramePositions = new Vec3Data[this->count];

	// Fill it
	for (unsigned int i = 0; i < this->count; i++)
	{
		FramePositions[i].Deserialize(in.framepositions((int)i));
	}
}
