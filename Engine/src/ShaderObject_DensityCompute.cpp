//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_DensityCompute.h"
// User generated headers... 
#include "DensitySolver.Cx.h"

namespace Azul
{
	ShaderObject_DensityCompute::~ShaderObject_DensityCompute()
	{

	}

	ShaderObject_DensityCompute::ShaderObject_DensityCompute(ShaderObject_DensityCompute::Name _name)
		: ShaderObject(_name)
	{
		this->CreateComputeShader(g_DensitySolver_Cx, sizeof(g_DensitySolver_Cx));
	}

}

// --- End of File ---
