//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_PressureGradientCompute.h"
#include "Mesh.h"

// User generated headers... 
#include "PressureGradientSolver.Cx.h"

namespace Azul
{
	ShaderObject_PressureGradientCompute::~ShaderObject_PressureGradientCompute()
	{

	}

	ShaderObject_PressureGradientCompute::ShaderObject_PressureGradientCompute(ShaderObject_PressureGradientCompute::Name _name)
		: ShaderObject(_name)
	{
		this->CreateComputeShader(g_PressureGradientSolver_Cx, sizeof(g_PressureGradientSolver_Cx));
	}

}

// --- End of File ---
