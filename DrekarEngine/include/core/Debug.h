#ifndef DE_DEBUG_H
#define DE_DEBUG_H

#include "export.h"

#include <string>
#include <fstream>
#include <iostream>

namespace de
{
	class DE_EXPORT Debug
	{
	protected:
		static Debug* sInstance;

		std::string mPath;

		Debug();

	public:
		static void Log(std::string pInfo);
	};
}

#endif
