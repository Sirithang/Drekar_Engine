#ifndef DE_ASSETDATABASE_H
#define DE_ASSETDATABASE_H

#include "export.h"

#include "core/Debug.h"

#include <string>
#include <map>

#include <typeinfo>

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
	* \brief this class allow to load an asset only once. If the asset is already loaded, it return a pointer to it.
	*		 NOTE :Never delete an asset loaded throught the database. Instead "unload" it.
	*/
	class DE_EXPORT AssetDatabase
	{
	protected:

		struct CountedAsset
		{
			int count;
			ILoadableAsset*	asset;
		};

		static AssetDatabase sInstance;

		std::map<std::string, CountedAsset> mAssets;

		AssetDatabase();

	public:
		template <class T>
		static T*	load(const std::string& pPath);
		template <class T>
		static T*	reload(const std::string& pPath);
		static void	unload(ILoadableAsset* pAsset);
	};


	//****** IMPLEMENTATION

	template <class T>
	T* AssetDatabase::load(const std::string& pPath)
	{
		if(sInstance.mAssets.count(pPath) == 0)
		{
			ILoadableAsset* p = (ILoadableAsset*)new T();
			p->fromFile(pPath);

			sInstance.mAssets[pPath].count = 1;
			sInstance.mAssets[pPath].asset = p;
		}
		else
		{
			sInstance.mAssets[pPath].count += 1;
		}

		return (T*)sInstance.mAssets[pPath].asset;
	}

	//-------

	template <class T>
	T* AssetDatabase::reload(const std::string& pPath)
	{
		if(sInstance.mAssets.count(pPath) == 0)
			return nullptr;

		sInstance.mAssets[pPath].asset->fromFile(pPath);

		return (T*)sInstance.mAssets[pPath].asset;
	}
}

#endif