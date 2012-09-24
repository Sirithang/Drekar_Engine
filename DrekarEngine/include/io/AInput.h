#ifndef DE_AINPUT_H
#define DE_AINPUT_H

#include "export.h"

#include <map>
#include <string>

namespace de
{
	namespace io
	{
		class AInput
		{
		protected:
			std::map<std::string, float>	mAxis;
			std::string							mName;
			std::string							mType;

			friend class InputManager;

		public:
			AInput(const std::string& pName, const std::string& pType);

			virtual void update() = 0;

			float getAxis(const std::string& pName) const;
		};
	}
}

#endif