//--------------------------------------------------------------

//--------------------------------------------------------------

#ifndef SHADER_OBJECT_VELOCITY_COMPUTE_H
#define SHADER_OBJECT_VELOCITY_COMPUTE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_VelocityCompute : public ShaderObject
	{
	public:

	public:
		ShaderObject_VelocityCompute() = delete;
		ShaderObject_VelocityCompute(const ShaderObject_VelocityCompute&) = delete;
		ShaderObject_VelocityCompute& operator = (const ShaderObject_VelocityCompute&) = delete;
		virtual ~ShaderObject_VelocityCompute();

		ShaderObject_VelocityCompute(ShaderObject_VelocityCompute::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
