#ifndef DE_RENDERER_H
#define DE_RENDERER_H

#include "export.h"
#include "core/AComponent.h"
#include "core/RenderBuffer.h"
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
			static Renderer* sCurrent;

			RenderBuffer			mRenderBuffer;
			RenderBuffer			mLightBuffer;

			std::list<AComponent*>	mRenderables;

			Material				mClearMaterial;
			Material				mCombineMaterial;

			//------ point light
			std::list<de::component::PointLight*>		mPointLights;
			Material									mPointLightsMat;
			data::Mesh									mPointLightsMesh;


			//------ directional light
			std::list<de::component::DirectionalLight*> mDirectionalLights;
			Material									mDiretionalLightMat;

			glm::vec3				mAmbient;
			
			void buildClearMat();
			void buildCombineMat();
			void buildLightBufferMat();

			void initDirectionalLights();
			void initPointLights();

			void renderDirectionalLights();
			void renderPointLights();

		public:
			Renderer();

			void setup();
			void render();

			void addRenderable(AComponent* pComponent);
			void removeRenderable(AComponent* pComponent);

			void addDirectionaLight(de::component::DirectionalLight* pLight);
			void addPointLight(de::component::PointLight* pLight);

			static Renderer* current();
		};
	}
}

#endif