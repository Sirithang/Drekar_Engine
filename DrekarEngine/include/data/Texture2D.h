#ifndef DE_TEXTURE2D_H
#define DE_TEXTURE2D_H

#include "data/Texture.h"
#include "core/AssetDatabase.h"

#include <string>

namespace de
{
	namespace data
	{
		class DE_EXPORT Texture2D : public de::data::Texture, public ILoadableAsset
		{
		public:

			void fromFile(const std::string& pPath);
		};
	}
}

#endif