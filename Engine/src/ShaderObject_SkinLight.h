//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_SKIN_LIGHT_TEXTURE_H
#define SHADER_OBJECT_SKIN_LIGHT_TEXTURE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_SkinLight : public ShaderObject
	{
	public:

	public:
		ShaderObject_SkinLight() = delete;
		ShaderObject_SkinLight(const ShaderObject_SkinLight&) = delete;
		ShaderObject_SkinLight& operator = (const ShaderObject_SkinLight&) = delete;
		virtual ~ShaderObject_SkinLight();

		ShaderObject_SkinLight(ShaderObject_SkinLight::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
