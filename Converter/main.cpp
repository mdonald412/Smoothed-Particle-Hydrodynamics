//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "ConvertModel.h"
#include "CreateTexture.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"
#include "ConvertAnim.h"
#include "ChickenBot.h"
#include "SpriteMesh.h"
#include "ConvertXML.h"
#include "ConvertSkeleton.h"
#include "ConvertSkin.h"
#include "ConvertHierarchy.h"

using namespace Azul;

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Sprite
	//CreateSpriteMesh("Sprite");

	//// Test Images 
	//CreateTexturePNG("TEST_PNG_RGB.png", "TEST_PNG_RGB");
	//CreateTexturePNG("TEST_PNG_RGBA.png", "TEST_PNG_RGBA");
	//CreateTextureTGA("TEST_TGA_BGR.tga", "TEST_TGA_BGR");
	//CreateTextureTGA("TEST_TGA_BGRA.tga", "TEST_TGA_BGRA");

	CreateCubeMesh();
	CreateSphereMesh();

	
	// Font stuff
	CreateTextureTGA("White.tga","White");
	//ConvertXML("MetricsArial36","Arial36");
	//         
	//// Space Frigate
	//CreateTextureTGA("space_frigate.tga","SpaceFrigate");
	//ConvertModel("space_frigate.glb","SpaceFrigate");

	//// ChickenBot	
	//// CreateChickenBotModels();
	//CreateTexturePNG("Ch14_1001_Diffuse.png","Mouse"); 
	//ConvertSkin("Dog", "Mouse");
	//ConvertAnim("Mousey_Run_Forward","Mouse_Run"); // Perform compression right here...
	//ConvertAnim("Mousey_Gangnam_Style","Mouse_Kpop"); // Perform compression right here...
	//ConvertAnim("Mousey_Tut_Hip_Hop_Dance","Mouse_Tut"); // Perform compression right here...
	//ConvertAnim("Mousey_Twist_Dance","Mouse_Twist"); // Perform compression right here...
	//ConvertAnim("Mousey_Shuffling","Mouse_Shuffling"); // Perform compression right here...
	//ConvertSkeleton("Dog", "Mouse");
	//ConvertHierarchy("Dog", "Mouse");
	//ConvertInvBind("Dog", "Mouse");

	//CreateTexturePNG("ChickenbotDiffuse.png", "ChickenBot");
	//ConvertSkin("walk_mesh", "Chickenbot");
	//ConvertAnim("walk_mesh", "ChickenBot_Walk");
	//ConvertSkeleton("walk_mesh", "ChickenBot");
	//ConvertHierarchy("walk_mesh", "ChickenBot");
	//ConvertInvBind("walk_mesh", "ChickenBot");
	// 
	//// clean up data directory
	system("del *.png");
	system("del *.tga");
	system("del *.glb");
	system("del *.xml");

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// ---  End of File ---------------
