//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef GLYPH_PROTO_H
#define GLYPH_PROTO_H

#include "TextureObject.h"

namespace Azul
{
	class GlyphProto
	{
	public:
		// Data
		GlyphProto(const char *const pMeshFileName, TextureObject::Name texName);

		GlyphProto() = delete;
		GlyphProto(const GlyphProto &) = delete;
		GlyphProto &operator = (GlyphProto &) = delete;
		virtual ~GlyphProto();

	public:

	};
}

#endif

//--- End of File ---

