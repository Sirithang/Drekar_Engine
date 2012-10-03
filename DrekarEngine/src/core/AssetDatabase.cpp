#include "core/AssetDatabase.h"

using namespace de;

AssetDatabase	AssetDatabase::sInstance;

//*************************************************

AssetDatabase::AssetDatabase()
{
	Debug::Log(std::string("Init AssetDB ") + typeid(this).name());
}

///************************************************

void AssetDatabase::unload(ILoadableAsset* pAsset)
{
	if(sInstance.mAssets.count(pAsset->path) > 0)
	{
		sInstance.mAssets[pAsset->path].count -= 1;

		if(sInstance.mAssets[pAsset->path].count <= 0)
			delete sInstance.mAssets[pAsset->path].asset;
	}
}