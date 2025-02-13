//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_FLAT_TEXTURE_INSTANCE_H
#define GRAPHICS_OBJECT_FLAT_TEXTURE_INSTANCE_H

#include "GraphicsObject.h"
#include "TextureObject.h"

namespace Azul
{
	class GraphicsObject_FlatTextureInstance :public GraphicsObject
	{
	public:
		GraphicsObject_FlatTextureInstance(Mesh::Name meshName,
			ShaderObject::Name shaderName,
			TextureObject* pTex,
			int instanceCount);

		GraphicsObject_FlatTextureInstance() = delete;
		GraphicsObject_FlatTextureInstance(const GraphicsObject_FlatTextureInstance&) = delete;
		GraphicsObject_FlatTextureInstance& operator = (const GraphicsObject_FlatTextureInstance&) = delete;
		virtual ~GraphicsObject_FlatTextureInstance();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		void pushWorld(Vec3 instanceWorld, int index);

		// data:  place uniform instancing here

		TextureObject* pTex;

		int instanceCount;

		ID3D11Buffer* poInstanceData;
		ID3D11Buffer* poConstantBuff_instanceWorld;

		Vec3* poLocalInstanceData;
		//unsigned int* poIndexData;

		Vec3* poLightColor;
		Vec3* poLightPos;

	};
}

#endif


// --- End of File ---
