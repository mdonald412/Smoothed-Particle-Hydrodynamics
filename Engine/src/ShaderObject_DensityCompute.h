//--------------------------------------------------------------

//--------------------------------------------------------------

#ifndef SHADER_OBJECT_DENSITY_COMPUTE_H
#define SHADER_OBJECT_DENSITY_COMPUTE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_DensityCompute : public ShaderObject
	{
	public:

	public:
		ShaderObject_DensityCompute() = delete;
		ShaderObject_DensityCompute(const ShaderObject_DensityCompute&) = delete;
		ShaderObject_DensityCompute& operator = (const ShaderObject_DensityCompute&) = delete;
		virtual ~ShaderObject_DensityCompute();

		ShaderObject_DensityCompute(ShaderObject_DensityCompute::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
