//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_CONST_COLOR_INSTANCE_H
#define GRAPHICS_OBJECT_CONST_COLOR_INSTANCE_H

#include "GraphicsObject.h"
#include "TextureObject.h"

namespace Azul
{

	class GraphicsObject_ConstColorInstance :public GraphicsObject
	{
	public:
		GraphicsObject_ConstColorInstance(Mesh::Name meshName,
										  ShaderObject::Name shaderName,
										  Vec3 &_pLightColor,
										  int instanceCount);

		GraphicsObject_ConstColorInstance() = delete;
		GraphicsObject_ConstColorInstance(const GraphicsObject_ConstColorInstance &) = delete;
		GraphicsObject_ConstColorInstance &operator = (const GraphicsObject_ConstColorInstance &) = delete;
		virtual ~GraphicsObject_ConstColorInstance();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		void pushWorld(Mat4 instanceWorld, int index);

		// data:  place uniform instancing here
		Vec3 *poLightColor;
		int instanceCount;
		
		ID3D11Buffer* poInstanceData;
		ID3D11Buffer* poConstantBuff_instanceWorld;

		Mat4* poLocalInstanceData;
		unsigned int* poIndexData;
		//Vec3f* poLocalInstanceData;

	};

}

#endif

// --- End of File ---
