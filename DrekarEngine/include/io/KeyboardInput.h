#ifndef DE_KEYBOARDINPUT_H
#define DE_KEYBOARDINPUT_H

#include "export.h"
#include "io/AInput.h"

#include <list>

namespace de
{
	namespace io
	{
		class DE_EXPORT KeyboardInput: public AInput
		{
		protected:
			struct SpecialKey
			{
				std::string name;
				int			ID;
			};

			std::list<SpecialKey> mSpecialKeys;

		public:
			KeyboardInput(const std::string& pName);

			void update();
		};
	}
}

#endif