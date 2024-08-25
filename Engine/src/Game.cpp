#include <d3d11.h>
#include <d3dcompiler.h>
#include <WinUser.h>
#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Camera.h"
#include "Colors.h"
#include "GameObject.h"
#include "GameObjectAnimSkin.h"
#include "ShaderObject.h"
#include "ShaderObject_ColorByVertex.h"
#include "ShaderObject_FlatTexture.h"
#include "ShaderObject_SkinFlatTexture.h"
#include "ShaderObject_LightTexture.h"
#include "ShaderObject_DensityCompute.h"
#include "ShaderObject_SkinLight.h"
#include "ShaderObject_ConstColor.h"
#include "ShaderObject_Sprite.h"
#include "ShaderObject_MixerCompute.h"
#include "ShaderObject_WorldCompute.h"
#include "ShaderObject_PressureGradientCompute.h"
#include "ShaderObject_VelocityCompute.h"
#include "Mesh.h"
#include "MeshProto.h"
#include "GraphicsObject_ColorByVertex.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_SkinFlatTexture.h"
#include "GraphicsObject_LightTexture.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_SkinLight.h"
#include "GraphicsObject_Sprite.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderObjectNodeMan.h"
#include "TextureObject.h"
#include "TextureProto.h"
#include "TexNodeMan.h"
#include "DirectXDeviceMan.h"
#include "CameraMan.h"
#include "CameraDemoInput.h"
#include "CameraMesh.h"
#include "AnimTimer.h"
#include "MathApp.h"
#include "Anim.h"
#include "GameObjectBasic.h"
#include "GameObjectCube.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"
#include "Image.h"
#include "ImageMan.h"
#include "Sprite.h"
#include "GlyphMan.h"
#include "SPHMan.h"
#include "HierarchyMan.h"
#include "InvBindMan.h"
#include "AnimControllerMan.h"
#include "ShaderObject_ConstColorInstance.h"
#include "ShaderObject_FlatTextureInstance.h"

#include "FontSprite.h"
#include "SkelMan.h"
#include "ClipMan.h"

#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "Mixer.h"
#include "WorldCompute.h"
#include "WCSPH_Solver.h"


using namespace Azul;

namespace Azul
{

	// Todo: clean up
	AnimController *pAnimController;
	FontSprite *pFontSprite1;
	AnimTime currTime;
	bool written;

	Vec3 universalVelocity;
	//-----------------------------------------------------------------------------
	//  Game::Game()
	//		Game Engine Constructor
	//-----------------------------------------------------------------------------

	Game::Game(const char *const pName, int width, int height)
		: Engine(pName, width, height)
	{
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	//  Game::~Game()
	//		Game Engine destructor
	//-----------------------------------------------------------------------------
	Game::~Game()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------

	SPH_Sphere* sphere_01;
	SPH_Sphere* sphere_02;
	SPH_Sphere* sphere_03;
	SPH_Sphere* sphere_04;
	Vec3 Adder(0.03f, 0.01f, 0.02f);
	Vec3 Adder2(0.01f, 0.015f, 0.02f);
	Vec3 Adder3(0.02f, 0.03f, -0.01f);
	Vec3 Adder4(0.02f, -0.02f, 0.01f);


	bool Game::LoadContent()
	{
		ShaderObjectNodeMan::Create();
		MeshNodeMan::Create();
		GameObjectMan::Create();
		TexNodeMan::Create();
		CameraMan::Create();
		ImageMan::Create();
		GlyphMan::Create();
		SkelMan::Create();
		ClipMan::Create();
		HierarchyMan::Create();
		InvBindMan::Create();
		AnimControllerMan::Create();

		// --------------------------
		// Camera setup
		// --------------------------

		// Camera_0		

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 3D perspective Camera
		//---------------------------------------------------------------------------------------------------------

		Camera *pCam0 = new Camera(Camera::Type::PERSPECTIVE_3D);

		pCam0->setViewport(0, 0, this->WindowWidth, this->WindowHeight);
		pCam0->setPerspective(35.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 1.0f, 10000.0f);

		pCam0->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f),
									Vec3(0.0f, -2.0f, 0.0f),
									Vec3(0.0f, 5.0f, 10.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent(Camera::Name::CAMERA_0, Camera::Type::PERSPECTIVE_3D);

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 2D orthographic Camera
		//---------------------------------------------------------------------------------------------------------

		Camera *pCam2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

		pCam2D->setViewport(0, 0, this->WindowWidth, this->WindowHeight);
		pCam2D->setOrthographic((float)-pCam2D->getScreenWidth() / 2.0f, (float)pCam2D->getScreenWidth() / 2.0f,
								(float)-pCam2D->getScreenHeight() / 2.0f, (float)pCam2D->getScreenHeight() / 2.0f,
								1.0f, 1000.0f);
		pCam2D->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));

		// Holder for the current 2D  cameras
		CameraMan::Add(Camera::Name::CAMERA_1, pCam2D);
		CameraMan::SetCurrent(Camera::Name::CAMERA_1, Camera::Type::ORTHOGRAPHIC_2D);


		// --------------------------------
		//  Mesh
		// --------------------------------

		Mesh* poCube = new MeshProto("CubeMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::CUBE, poCube);

		poCube = new MeshProto("SphereMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::SPHERE, poCube);		

		TextureObject* poTex = new TextureProto("White.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Brick, poTex);


		// --------------------------------
		//  Shader
		// --------------------------------

		ShaderObject *poShaderA3 = new ShaderObject_ConstColorInstance(ShaderObject::Name::ConstColorInstance);
		ShaderObject *poShaderA4 = new ShaderObject_ConstColor(ShaderObject::Name::ConstColor);
		ShaderObject* poShaderA5 = new ShaderObject_FlatTextureInstance(ShaderObject::Name::FlatTextureInstance);
		ShaderObject* poShaderA6 = new ShaderObject_DensityCompute(ShaderObject::Name::DensityCompute);
		ShaderObject* poShaderA7 = new ShaderObject_PressureGradientCompute(ShaderObject::Name::PressureGradientCompute);
		ShaderObject* poShaderA8 = new ShaderObject_VelocityCompute(ShaderObject::Name::VelocityCompute);

		ShaderObjectNodeMan::Add(poShaderA3);
		ShaderObjectNodeMan::Add(poShaderA4);
		ShaderObjectNodeMan::Add(poShaderA5);
		ShaderObjectNodeMan::Add(poShaderA6);
		ShaderObjectNodeMan::Add(poShaderA7);
		ShaderObjectNodeMan::Add(poShaderA8);

		SPHMan::Create();

		int i = 0;
		float scalar = 2.0f;
		float scalar2 = 5.0f;
		float scalar3 = 2.0f;
		while (i < NUM_SPHERES)
		{
			float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (scalar*SMOOTH_RADIUS))) - (float)(scalar * (SMOOTH_RADIUS / scalar));
			float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (scalar2*SMOOTH_RADIUS))) - (float)(scalar * (SMOOTH_RADIUS / scalar));
			float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (scalar3*SMOOTH_RADIUS))) - (float)(scalar * (SMOOTH_RADIUS / scalar));
			
			SPH_Sphere* newSphere = SPHMan::AddSphere(5.0f, Vec3(x - 1.0f, y - 1.0f, z - 1.0f), 0.05f, SPH_Sphere::Active);
			*newSphere->Velocity = Vec3(0.0f, 0.0f, 0.0f);
			newSphere->index = i;
			i++;
		}

		currTime = this->globalTimer.Toc();

		written = false;


		SPH_Strategy::Read();


		return true;
	}


	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float)
	{
		this->intervalTimer.Toc();
		this->intervalTimer.Tic();

		// -----------------------
		// Read inputs
		// -----------------------
		CameraDemoInput();
		std::vector<SPH_Sphere*> mySpheres = SPHMan::GetSpheresList();
		int i = 0;
		*mySpheres[1]->Velocity += universalVelocity;
		i++;


		// ------------------------------------
		// Camera update
		// ------------------------------------
		
		CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->updateCamera();

		AnimControllerMan::Update();

		// ------------------------------------
		// Update GameObjects
		// ------------------------------------
		AnimTime diffTime = this->globalTimer.Toc() - currTime;
		currTime = this->globalTimer.Toc();
		AnimTime frame = AnimTime(AnimTime::Duration::ONE_SECOND);
		float timePrint = diffTime / frame;

		Trace::out("%d\n", timePrint);
	

		//// Set up for writing...
		//if (SPH_Strategy::frame < FRAME_COUNT)
		//{
		//	SPHMan::Update(diffTime);
		//}
		//else if(!written)
		//{
		//	SPH_Strategy::Write();
		//	written = true;
		//}
		//else
		//{
		//}


		if (SPH_Strategy::frame < FRAME_COUNT)
		{
			SPHMan::Update(diffTime);
		}
		SPH_Strategy::frame++;


		GameObjectMan::Update(this->globalTimer.Toc());

	}

	//-----------------------------------------------------------------------------
	// Game::Render()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Render()
	{
		this->SetDefaultTargetMode();

		GameObjectMan::Draw();
		//Sleep(1000);
	}

	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnloadContent()
	{
		InvBindMan::Destroy();
		HierarchyMan::Destroy();
		ClipMan::Destroy();
		SkelMan::Destroy();
		GlyphMan::Destroy();
		ImageMan::Destroy();
		CameraMan::Destroy();
		ShaderObjectNodeMan::Destroy();
		MeshNodeMan::Destroy();
		GameObjectMan::Destroy();
		TexNodeMan::Destroy();
		DirectXDeviceMan::Destroy();
		AnimControllerMan::Destroy();
		SPHMan::Destroy();
		SPH_Strategy::Destroy();
		WCSPH_Solver::Destroy();
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	// 
	// Clear the color and depth buffers.
	//------------------------------------------------------------------
	void Game::ClearDepthStencilBuffer()
	{
#ifdef _DEBUG
		const Vec4 ClearColor = Azul::Colors::LightGray;
#else
		const Vec4 ClearColor = Azul::Colors::Wheat;
#endif
		float clearDepth = 1.0f;
		uint8_t clearStencil = 0;
		g_d3dDeviceContext->ClearRenderTargetView(g_d3dRenderTargetView, (const float *)&ClearColor);
		g_d3dDeviceContext->ClearDepthStencilView(g_d3dDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
	}

}

// --- End of File ---
