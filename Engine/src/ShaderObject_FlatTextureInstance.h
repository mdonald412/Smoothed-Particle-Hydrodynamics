//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_FLAT_TEXTURE_INSTANCE_H
#define SHADER_OBJECT_FLAT_TEXTURE_INSTANCE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_FlatTextureInstance : public ShaderObject
	{
	public:

	public:
		ShaderObject_FlatTextureInstance() = delete;
		ShaderObject_FlatTextureInstance(const ShaderObject_FlatTextureInstance&) = delete;
		ShaderObject_FlatTextureInstance& operator = (const ShaderObject_FlatTextureInstance&) = delete;
		virtual ~ShaderObject_FlatTextureInstance();

		ShaderObject_FlatTextureInstance(ShaderObject_FlatTextureInstance::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
