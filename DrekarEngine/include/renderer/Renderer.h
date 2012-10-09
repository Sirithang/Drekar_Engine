#ifndef DE_RENDERER_H
#define DE_RENDERER_H

#include "export.h"
#include "core/AComponent.h"
#include "core/RenderBuffer.h"
#include "core/ARenderable.h"
#include "core/Material.h"
#include "component/light/DirectionalLight.h"
#include "component/light/PointLight.h"

#include <list>

namespace de
{
	namespace renderer
	{
		/**
		* \biref this class manage the list of renderable and the setup
		* of all he lights and buffer. Each AScreen got his own renderer.
		*/
		class DE_EXPORT Renderer
		{
		protected:
			typedef std::multimap<uint32_t, ARenderable*>  multimap_renderer;

			static Renderer* sCurrent;

			RenderBuffer			mRenderBuffer;
			RenderBuffer			mLightBuffer;

			Material				mClearMaterial;
			Material				mCombineMaterial;

			de::data::Texture*		mAlbedo;
			de::data::Texture*		mNormal;
			de::data::Texture*		mDepth;

			glm::vec3				mAmbient;

			multimap_renderer		mOrderedList;
			
			void buildClearMat();
			void buildCombineMat();
			void buildLightBufferMat();

			void initDirectionalLights();
			void initPointLights();

		public:
			Renderer();

			void setup();
			void render();

			void setAmbient(const glm::vec3& pAmbientColor);

			static Renderer* current();

			void sortRenderList();
			void renderOpaque();
		};
	}
}

#endif