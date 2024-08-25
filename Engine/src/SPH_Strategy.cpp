#include "SPH_Strategy.h"
#include "SPH_Stats.h"
#include "File.h"

int SPH_Strategy::frame;
SPH_Scene* SPH_Strategy::myScene;
bool SPH_Strategy::cached;

void SPH_Strategy::initialize(int count)
{
	myScene = new SPH_Scene(FRAME_COUNT, NUM_SPHERES);
	cached = false;
	frame = 0;
}

void SPH_Strategy::RecordFrame(Vec3* pBuff)
{
	// This is where we will cache...

	// So myList corresponds to the current state or frame of the simulation,
	// so we need to pack the frame ... first make SPH_Scene class...

	myScene->HandleFrame(pBuff, frame);
	Trace::out("Hello");
}

void SPH_Strategy::Destroy()
{
	delete myScene;
}

void SPH_Strategy::solveParticles(std::vector<SPH_Sphere*>* inList)
{
	if (cached)
	{
		int i = 0;
		int max = (int)inList->size();
		while (i < max)
		{
			inList->at(i)->position->x(myScene->Frames[frame].FramePositions[i].x);// = myScene->Frames[frame].FramePositions[i].x;
			inList->at(i)->position->y(myScene->Frames[frame].FramePositions[i].y);// = myScene->Frames[frame].FramePositions[i].x;
			inList->at(i)->position->z(myScene->Frames[frame].FramePositions[i].z);// = myScene->Frames[frame].FramePositions[i].x;
			i++;
		}
	}
}

void SPH_Strategy::Write()
{
	SPH_Scene_proto SPH_proto;
	myScene->Serialize(SPH_proto);

	File::Handle fh;
	File::Error err;

	const char* pProtoFileType = ".i";

	// Create output name
	std::string OutputFileName = "SPH.proto.sim";
	Trace::out(" --> %s\n", OutputFileName.c_str());
	err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
	assert(err == File::Error::SUCCESS);

	std::string strOut;
	SPH_proto.SerializeToString(&strOut);

	File::Write(fh, strOut.data(), strOut.length());
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);
}

void SPH_Strategy::Read()
{

	// File stuff
	File::Handle fh;
	File::Error  ferror;
	
	ferror = File::Open(fh, "SPH.proto.sim", File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);
	
	// Get the size
	ferror = File::Seek(fh, File::Position::END, 0);
	assert(ferror == File::Error::SUCCESS);
	
	DWORD length;
	ferror = File::Tell(fh, length);
	assert(ferror == File::Error::SUCCESS);
	
	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);
	
	char* poBuff = new char[length];
	assert(poBuff);
	
	ferror = File::Read(fh, poBuff, length);
	assert(ferror == File::Error::SUCCESS);
	
	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);
	
	// Now the raw data is poBUff
	// deserialize the data --> mB
	std::string strIn(poBuff, length);
	SPH_Scene_proto mB_proto;
	
	mB_proto.ParseFromString(strIn);
	
	//myScene = new SPH_Scene(FRAME_COUNT, NUM_SPHERES);
	myScene->Deserialize(mB_proto);
	delete[] poBuff;

	cached = true;
	frame = 0;
}