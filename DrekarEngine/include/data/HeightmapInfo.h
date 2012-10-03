#ifndef DE_HEIGHTMAPINFO_H
#define DE_HEIGHTMAPINFO_H

#include "export.h"

#include <string>

namespace de
{
	namespace data
	{
		struct DE_EXPORT HeightmapInfo
		{
			float width;
			float depth;
			float height;

			int		hmWidth;
			int		hmHeight;
			float* heightInfo;

			//*****
			HeightmapInfo();
			~HeightmapInfo();

			void fromJSON(const std::string& pData);
		};
	}
}

#endif