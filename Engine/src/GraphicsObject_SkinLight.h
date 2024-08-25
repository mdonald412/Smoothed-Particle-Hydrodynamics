//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_SKIN_LIGHT_TEXTURE_H
#define GRAPHICS_OBJECT_SKIN_LIGHT_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureObject.h"
#include "Mixer.h"
#include "WorldCompute.h"

namespace Azul
{
	class GraphicsObject_SkinLight :public GraphicsObject
	{
	public:

		GraphicsObject_SkinLight() = delete;
		GraphicsObject_SkinLight(const GraphicsObject_SkinLight&) = delete;
		GraphicsObject_SkinLight& operator = (const GraphicsObject_SkinLight&) = delete;
		virtual ~GraphicsObject_SkinLight();

		GraphicsObject_SkinLight(Mesh::Name meshName, ShaderObject::Name shaderName, TextureObject::Name textName, Mixer* _pMixer, WorldCompute* _pWorldCompute, Vec3 pLightCol, Vec3 pLightPos);

		// Render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// ---------------------------------------------
		// Data
		// ---------------------------------------------
		TextureObject* pTex;

		// Compute Data
		Mixer* pMixer;
		WorldCompute* pWorldCompute;

		Vec3* poLightColor;
		Vec3* poLightPos;


	};
}

#endif


// --- End of File ---
