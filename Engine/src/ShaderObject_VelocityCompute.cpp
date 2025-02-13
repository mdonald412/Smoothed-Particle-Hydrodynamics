//--------------------------------------------------------------

//--------------------------------------------------------------

#include "ShaderObject_VelocityCompute.h"
// User generated headers... 
#include "VelocitySolver.Cx.h"

namespace Azul
{
	ShaderObject_VelocityCompute::~ShaderObject_VelocityCompute()
	{

	}

	ShaderObject_VelocityCompute::ShaderObject_VelocityCompute(ShaderObject_VelocityCompute::Name _name)
		: ShaderObject(_name)
	{
		this->CreateComputeShader(g_VelocitySolver_Cx, sizeof(g_VelocitySolver_Cx));
	}

}

// --- End of File ---
