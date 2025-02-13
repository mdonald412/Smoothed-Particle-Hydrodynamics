//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_SkinLight.h"
#include "CameraMan.h"
#include "GameMan.h"
#include "TexNodeMan.h"
#include "DirectXDeviceMan.h"
#include "ComputeRSVBuffer.h"
#include "ShaderMappings.h"

namespace Azul
{
	GraphicsObject_SkinLight::~GraphicsObject_SkinLight()
	{
		delete this->poLightColor;
		delete this->poLightPos;
	}

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_SkinLight::GraphicsObject_SkinLight(Mesh::Name meshName,
		ShaderObject::Name shaderName,
		TextureObject::Name textName,
		Mixer* _pMixer,
		WorldCompute* _pWorldCompute,
		Vec3 pLightCol,
		Vec3 pLightPos)
		: GraphicsObject(meshName, shaderName),
		pTex{ nullptr },
		pMixer{ _pMixer },
		pWorldCompute{ _pWorldCompute }
	{
		poLightColor = new Vec3(pLightCol);
		poLightPos = new Vec3(pLightPos);

		this->pTex = TexNodeMan::Find(textName);
		assert(pTex);
		assert(pMixer);
		assert(pWorldCompute);
	}


	void GraphicsObject_SkinLight::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		this->pTex->ActivateTexture();
	}

	void GraphicsObject_SkinLight::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		Camera* pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);

		// Set the InvBind to Vertex shader
		assert(pWorldCompute->poVsInvBind);
		pWorldCompute->poVsInvBind->BindVertex(ShaderResourceBufferSlot::InvBind);

		// Set the BoneWorld to Vertex shader
		assert(pWorldCompute->poVsBoneWorld);
		pWorldCompute->poVsBoneWorld->BindVertex(ShaderResourceBufferSlot::BoneWorldIn);

		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightPos, 0, nullptr, poLightPos, 0, 0);
	}

	void GraphicsObject_SkinLight::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_SkinLight::RestoreState()
	{
		Game* pGame = GameMan::GetGame();
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		UINT sampleMask = 0xffffffff;
		pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateOff, blendFactor, sampleMask);
	}

}

// --- End of File ---
