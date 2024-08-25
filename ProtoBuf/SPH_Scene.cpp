#include "SPH_Scene.h"
#include "SPH_Frame.h"

Azul::SPH_Scene::SPH_Scene(int _count, int _numSpheres)
{
	this->count = _count;
	this->Frames = new SPH_Frame[count];

	int i = 0;
	while (i < count)
	{
		this->Frames[i].FramePositions = new Vec3Data[_numSpheres];
		this->Frames[i].count = _numSpheres;
		i++;
	}
}

Azul::SPH_Scene::~SPH_Scene()
{
	delete[] this->Frames;
}

void Azul::SPH_Scene::HandleFrame(Vec3* positions, int frameCount)
{
	this->Frames[frameCount].PackFrame(positions);
}


void Azul::SPH_Scene::Serialize(SPH_Scene_proto& out) const
{
	out.set_framecount(count);
	int i = 0;
	while (i < count)
	{
		SPH_Frame_proto tmpVec3_proto;
		this->Frames[i].Serialize(tmpVec3_proto);
		*out.add_frames() = tmpVec3_proto;
		i++;
	}
}

void Azul::SPH_Scene::Deserialize(const SPH_Scene_proto& in)
{
	this->count = in.framecount();

	// Fill it
	for (unsigned int i = 0; i < this->count; i++)
	{
		Frames[i].Deserialize(in.frames((int)i));
	}
}