//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_SkinLight.h"
#include "MeshLayout.h"
#include "ShaderMappings.h"

// User generated headers... 
#include "SkinLight.Px.h"
#include "SkinLight.Vx.h"

namespace Azul
{
	ShaderObject_SkinLight::~ShaderObject_SkinLight()
	{

	}

	ShaderObject_SkinLight::ShaderObject_SkinLight(ShaderObject_SkinLight::Name _name)
		: ShaderObject(_name)
	{
		this->CreateVertexShader(g_SkinLight_VxShader, sizeof(g_SkinLight_VxShader));

		// Create the input layout for the vertex shader.
		D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Position, offsetof(VertexPos,Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, (uint32_t)VertexSlot::TexCoord, offsetof(VertexTexCoord,TexCoord),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Norm, offsetof(VertexNorm,Norm),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT , (uint32_t)VertexSlot::Weights, offsetof(VertexWeights,Weight),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT  , (uint32_t)VertexSlot::Joints, offsetof(VertexJoints,Joint),  D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		this->CreateInputLayout(g_SkinLight_VxShader,
			sizeof(g_SkinLight_VxShader),
			vertexLayoutDesc,
			sizeof(vertexLayoutDesc));

		this->CreatePixelShader(g_SkinLight_PxShader,
			sizeof(g_SkinLight_PxShader));



	}

}

// --- End of File ---
