#ifndef DE_DIRECTIONALLIGHT_H
#define DE_DIRECTIONALLIGHT_H

#include "export.h"
#include "core/ComponentFactory.h"
#include "data/Texture2D.h"
#include "component/Camera.h"
#include "core/Material.h"
#include "core/RenderBuffer.h"
#include "component/light/Light.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT DirectionalLight : public Light
		{
			COMPONENT_DEC_TYPE(DirectionalLight);

		protected:
			static Material*	sDiretionalLightMat;

			RenderBuffer		mShadowmapBuffer;
			data::Texture		mShadowmap;

			GameObject*			mLightGameobject;
			Camera*				mLightCamera;

		public:
			DirectionalLight();

			void init();
			void setup();

			void setupLightType(de::data::Texture* pAlbedo, de::data::Texture* pNormal, de::data::Texture* pDepth);

			void renderShadowmap();
		};
	}
}

#endif