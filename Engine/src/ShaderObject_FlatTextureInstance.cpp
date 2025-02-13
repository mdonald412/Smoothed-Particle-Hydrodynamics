//--------------------------------------------------------------

//--------------------------------------------------------------

#include "ShaderObject_FlatTextureInstance.h"
#include "MeshLayout.h"
#include "ShaderMappings.h"

// User generated headers... 
#include "FlatTextureInstance.Px.h"
#include "FlatTextureInstance.Vx.h"

namespace Azul
{
	ShaderObject_FlatTextureInstance::~ShaderObject_FlatTextureInstance()
	{

	}

	ShaderObject_FlatTextureInstance::ShaderObject_FlatTextureInstance(ShaderObject_FlatTextureInstance::Name _name)
		: ShaderObject(_name)
	{
		this->CreateVertexShader(g_FlatTextureInstance_VxShader, sizeof(g_FlatTextureInstance_VxShader));

		// Create the input layout for the vertex shader.
		D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Position, offsetof(VertexPos,Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD"   , 0, DXGI_FORMAT_R32G32_FLOAT, (uint32_t)VertexSlot::TexCoord, offsetof(VertexTexCoord,TexCoord),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Norm, offsetof(VertexNorm,Norm),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "SV_InstanceID", 0, DXGI_FORMAT_R32_SINT, (uint32_t)VertexSlot::InstanceData, offsetof(InstancePos,Position), D3D11_INPUT_PER_INSTANCE_DATA}
		};

		this->CreateInputLayout(g_FlatTextureInstance_VxShader, sizeof(g_FlatTextureInstance_VxShader), vertexLayoutDesc, sizeof(vertexLayoutDesc));

		this->CreatePixelShader(g_FlatTextureInstance_PxShader, sizeof(g_FlatTextureInstance_PxShader));

	}

}

// --- End of File ---
