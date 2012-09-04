#ifndef DE_POINTLIGHT_H
#define DE_POINTLIGHT_H

#include "export.h"
#include "component/light/Light.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT PointLight : public Light
		{
		protected:
			float mRange;

		public:
			void init();
			void setup(Program* pProg);

			float range() const;
		};
	}
}

#endif