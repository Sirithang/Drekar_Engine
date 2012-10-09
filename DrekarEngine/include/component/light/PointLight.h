#ifndef DE_POINTLIGHT_H
#define DE_POINTLIGHT_H

#include "export.h"
#include "core/Material.h"
#include "data/Mesh.h"
#include "component/light/Light.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT PointLight : public Light
		{
		protected:
			static de::Material*	sPointLightMaterial;
			static de::data::Mesh*	sMesh;


			float mRange;

		public:
			PointLight();

			void init();
			void setup();

			void setupLightType(de::data::Texture* pAlbedo, de::data::Texture* pNormal, de::data::Texture* pDepth);

			float range() const;

			void renderShadowmap();
		};
	}
}

#endif