//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_FlatTextureInstance.h"
#include "CameraMan.h"
#include "GameMan.h"
#include "DirectXDeviceMan.h"
#include "ShaderMappings.h"
#include "SPHMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_FlatTextureInstance::GraphicsObject_FlatTextureInstance(Mesh::Name meshName,
		ShaderObject::Name shaderName,
		TextureObject* _pTex,
		int _instanceCount)
		: GraphicsObject(meshName, shaderName),
		pTex(_pTex),
		poInstanceData(nullptr),
		instanceCount(_instanceCount),
		poLightColor(nullptr),
		poLightPos(nullptr)
	{
			assert(pTex);

			poLightColor = new Vec3(0.5f, 0.5f, 1);
			poLightPos = new Vec3(10, 10, 10);

			this->poLocalInstanceData = new Vec3[instanceCount]();
			//this->poIndexData = new unsigned int[instanceCount]();

			this->pMesh->ActivateMesh();
			this->poConstantBuff_instanceWorld = this->pMesh->CreateConstantBuffer(sizeof(Mat4) * instanceCount);
	}

	GraphicsObject_FlatTextureInstance::~GraphicsObject_FlatTextureInstance()
	{
		SafeRelease(this->poConstantBuff_instanceWorld);
		delete poLightColor;
		delete poLightPos;
		delete[] this->poLocalInstanceData;
	}

	void GraphicsObject_FlatTextureInstance::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		this->pTex->ActivateTexture();

		if (this->pTex->HasAlpha())
		{
			Game* pGame = GameMan::GetGame();
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			UINT sampleMask = 0xffffffff;
			pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateAlpha, blendFactor, sampleMask);

		}
	}

	void GraphicsObject_FlatTextureInstance::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::csInstance, 1, &poConstantBuff_instanceWorld);
		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_instanceWorld,
			0, nullptr, poLocalInstanceData, 0, 0);


		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightPos, 0, nullptr, poLightPos, 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightPos, 0, nullptr, poLightPos, 0, 0);


		// w1(7)
		Camera* pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);
	}

	void GraphicsObject_FlatTextureInstance::Draw()
	{
		pMesh->RenderInstances(instanceCount);
	}

	void GraphicsObject_FlatTextureInstance::RestoreState()
	{
		Game* pGame = GameMan::GetGame();
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		UINT sampleMask = 0xffffffff;
		pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateOff, blendFactor, sampleMask);
	}

	void GraphicsObject_FlatTextureInstance::pushWorld(Vec3 instanceWorld, int index)
	{
		this->poLocalInstanceData[index] = instanceWorld;
	}


}

// --- End of File ---
