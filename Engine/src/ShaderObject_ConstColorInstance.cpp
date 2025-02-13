//--------------------------------------------------------------

//--------------------------------------------------------------

#include "ShaderObject_ConstColorInstance.h"
#include "MeshLayout.h"
#include "ShaderMappings.h"

// User generated headers... 
#include "ConstColorInstance.Px.h"
#include "ConstColorInstance.Vx.h"

namespace Azul
{
	ShaderObject_ConstColorInstance::~ShaderObject_ConstColorInstance()
	{

	}

	ShaderObject_ConstColorInstance::ShaderObject_ConstColorInstance(ShaderObject_ConstColorInstance::Name _name)
		: ShaderObject(_name)
	{
		this->CreateVertexShader(g_ConstColorInstance_VxShader, sizeof(g_ConstColorInstance_VxShader));

		// Create the input layout for the vertex shader.

		int offset = offsetof(VertexPos, Position);
		offset = offsetof(InstancePos, Position);
		D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Position, offsetof(VertexPos,Position), D3D11_INPUT_PER_VERTEX_DATA},
			{ "SV_InstanceID", 0, DXGI_FORMAT_R32_SINT, (uint32_t)VertexSlot::InstanceData, offsetof(InstancePos,Position), D3D11_INPUT_PER_INSTANCE_DATA}
		};

		this->CreateInputLayout(g_ConstColorInstance_VxShader, sizeof(g_ConstColorInstance_VxShader), vertexLayoutDesc, sizeof(vertexLayoutDesc));

		this->CreatePixelShader(g_ConstColorInstance_PxShader, sizeof(g_ConstColorInstance_PxShader));

	}

}

// --- End of File ---
