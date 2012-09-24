#ifndef DE_ASSETDATABASE_H
#define DE_ASSETDATABASE_H

#include "export.h"

#include <string>
#include <map>

namespace de
{
	/**
	* \brief a class describing an asset loadable from a fil (mesh, material...) must subclass that in order to be loadable throught AssetDatabase
	*		 BEWARE : path is read only, don't change it!
	*/
	class DE_EXPORT ILoadableAsset
	{
	public:
		virtual void fromFile(const std::string& pFile) = 0;

		std::string path;
	};

	//-----------------------------------

	/**
	* \brief this templated class allow to load an asset only once. If the asset is already loaded, it return a pointer to it.
	*		 NOTE :Never delete an asset loaded throught the database. Instead "unload" it.
	*/
	template <class T>
	class AssetDatabase
	{
	protected:

		template <class T>
		struct CountedAsset
		{
			int count;
			T*	asset;
		};

		static AssetDatabase* sInstance;

		std::map<std::string, CountedAsset<T> > mAssets;

	public:
		static T*	load(const std::string& pPath);
		static void	unload(ILoadableAsset* pAsset);
	};


	//****** IMPLEMENTATION

	template <class T>
	AssetDatabase<T>*	AssetDatabase<T>::sInstance = new AssetDatabase<T>();

	//-------

	template <class T>
	T* AssetDatabase<T>::load(const std::string& pPath)
	{
		if(sInstance->mAssets.count(pPath) == 0)
		{
			ILoadableAsset* p = (ILoadableAsset*)new T();
			p->fromFile(pPath);

			sInstance->mAssets[pPath].count = 1;
			sInstance->mAssets[pPath].asset = (T*)p;
		}
		else
		{
			sInstance->mAssets[pPath].count += 1;
		}

		return sInstance->mAssets[pPath].asset;
	}

	//-------

	template <class T>
	void AssetDatabase<T>::unload(ILoadableAsset* pAsset)
	{
		if(sInstance->mAssets.count(pAsset->path) > 0)
		{
			sInstance->mAssets[pAsset->path].count -= 1;

			if(sInstance->mAssets[pAsset->path].count <= 0)
				delete sInstance->mAssets[pAsset->path].asset;
		}
	}
}

#endif