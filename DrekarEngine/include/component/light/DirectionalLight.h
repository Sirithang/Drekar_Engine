#ifndef DE_DIRECTIONALLIGHT_H
#define DE_DIRECTIONALLIGHT_H

#include "export.h"
#include "core/ComponentFactory.h"
#include "component/light/Light.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT DirectionalLight : public Light
		{
			COMPONENT_DEC_TYPE(DirectionalLight);
		public:
			void init();
			void setup(Program* pProg);
		};
	}
}

#endif