//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#ifndef FRAME_BUCKET_H
#define FRAME_BUCKET_H

#include "AnimTime.h"

namespace Azul
{
	class ComputeRSVBuffer;

	class FrameBucket
	{
	public:

		FrameBucket();
		FrameBucket(const FrameBucket &) = delete;
		FrameBucket &operator=(const FrameBucket &) = delete;
		virtual ~FrameBucket();

		FrameBucket     *nextBucket;
		FrameBucket     *prevBucket;
		AnimTime         KeyTime; // Change here...
		ComputeRSVBuffer *poBoneRSV;
	};
}

#endif

// --- End of File ---
