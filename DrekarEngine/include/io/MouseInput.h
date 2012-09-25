#ifndef DE_MOUSEINPUT_H
#define DE_MOUSEINPUT_H

#include "export.h"
#include "io/AInput.h"

namespace de
{
	namespace io
	{
		class DE_EXPORT MouseInput : public AInput
		{
		public:
			MouseInput(const std::string& pName);

			void update();
		};
	}
}

#endif