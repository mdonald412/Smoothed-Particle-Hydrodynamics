//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_ConstColorInstance.h"
#include "Engine.h"
#include "DirectXDeviceMan.h"
#include "CameraMan.h"
#include "ShaderMappings.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_ConstColorInstance::GraphicsObject_ConstColorInstance(Mesh::Name meshName,
		ShaderObject::Name shaderName,
		Vec3& LightColor,
		int _instanceCount)
		: GraphicsObject(meshName, shaderName),
		poInstanceData(nullptr),
		poLightColor(nullptr),
		instanceCount(_instanceCount)

	{
		poLightColor = new Vec3(LightColor);
		assert(poLightColor);

		this->poLocalInstanceData = new Mat4[instanceCount]();
		this->poIndexData = new unsigned int[instanceCount]();

		this->pMesh->ActivateMesh();
		this->poConstantBuff_instanceWorld = this->pMesh->CreateConstantBuffer(sizeof(Mat4)*instanceCount);

	}

	GraphicsObject_ConstColorInstance::~GraphicsObject_ConstColorInstance()
	{
		delete poLightColor;
		delete[] poLocalInstanceData;
		delete[] poIndexData;
		SafeRelease(this->poConstantBuff_instanceWorld);

	}

	void GraphicsObject_ConstColorInstance::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
			// Need to do this properly...
		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;

		// To Do add scissor rectangle... its faster
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state object.
		ID3D11RasterizerState *pRasterState;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterState);
		assert(SUCCEEDED(hr));

		DirectXDeviceMan::GetContext()->RSSetState(pRasterState);

		SafeRelease(pRasterState);

	}

	void GraphicsObject_ConstColorInstance::SetDataGPU()
	{

		pShaderObj->ActivateShader();

		// Specialized behavior for instancing...
		const UINT offset = 0;

		DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::csInstance, 1, &poConstantBuff_instanceWorld);
		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_instanceWorld,
															0, nullptr, poLocalInstanceData, 0, 0);

		pMesh->ActivateMesh();

		// w1(7)
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);



		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);
	}

	void GraphicsObject_ConstColorInstance::Draw()
	{
		pMesh->RenderInstances(instanceCount);
	}

	void GraphicsObject_ConstColorInstance::RestoreState()
	{
		// Future - Undo settings to directX
			// Need to do this properly...
		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;

		// To Do add scissor rectangle... its faster
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state object.
		ID3D11RasterizerState *pRasterState;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterState);
		assert(SUCCEEDED(hr));

		DirectXDeviceMan::GetContext()->RSSetState(pRasterState);

		SafeRelease(pRasterState);
	}

	void GraphicsObject_ConstColorInstance::pushWorld(Mat4 instanceWorld, int index)
	{
		//Vec3f shortened(instanceWorld.x(), instanceWorld.y(), instanceWorld.z());
		this->poLocalInstanceData[index] = instanceWorld;
		this->poIndexData[index] = index;
	}

}

// --- End of File ---
