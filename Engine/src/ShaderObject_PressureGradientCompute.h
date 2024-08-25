//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_PRESSURE_COMPUTE_H
#define SHADER_OBJECT_PRESSURE_COMPUTE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_PressureGradientCompute : public ShaderObject
	{
	public:

	public:
		ShaderObject_PressureGradientCompute() = delete;
		ShaderObject_PressureGradientCompute(const ShaderObject_PressureGradientCompute&) = delete;
		ShaderObject_PressureGradientCompute& operator = (const ShaderObject_PressureGradientCompute&) = delete;
		virtual ~ShaderObject_PressureGradientCompute();

		ShaderObject_PressureGradientCompute(ShaderObject_PressureGradientCompute::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
