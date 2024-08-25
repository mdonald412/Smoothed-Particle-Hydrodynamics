//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_CONST_COLOR_INSTANCE_H
#define SHADER_OBJECT_CONST_COLOR_INSTANCE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_ConstColorInstance : public ShaderObject
	{
	public:

	public:
		ShaderObject_ConstColorInstance() = delete;
		ShaderObject_ConstColorInstance(const ShaderObject_ConstColorInstance &) = delete;
		ShaderObject_ConstColorInstance &operator = (const ShaderObject_ConstColorInstance &) = delete;
		virtual ~ShaderObject_ConstColorInstance();

		ShaderObject_ConstColorInstance(ShaderObject_ConstColorInstance::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
