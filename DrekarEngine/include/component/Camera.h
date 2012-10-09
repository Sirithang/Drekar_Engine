#ifndef DE_CAMERA_H
#define DE_CAMERA_H

#include "core/AComponent.h"
#include "core/ComponentFactory.h"
#include "core/Material.h"
#include <list>
#include <glm/glm.hpp>

namespace de
{
	namespace component
	{
		class DE_EXPORT Camera : public AComponent
		{
		protected:
			COMPONENT_DEC_TYPE(Camera);

			static std::list<Camera*> sCameraList;
			static Camera* sCurrent; // currently used camera

			glm::mat4 mProjection;
			glm::mat4 mView;

			float		mFov;
			float		mAspect;
			glm::vec2	mClipPlanes;

			bool		mIsOrtho;
			float		mOrthoHalfSize;

			bool		mRecomputeProjection;

			Material*	mReplacementMaterial;

			void computeProjection();

		public:
			void init();
			void update();

			void release();

			//----getter/setter

			void setFov(float pFov);
			void setAspect(float pAspect);
			void setClipPlane(glm::vec2& pClipPlane);
			void setOrtho(bool pOrtho);
			void setOrthoHalfSize(float pHalfSize);

			void setReplacementMaterial(Material* pMaterial);

			float		fov() const;
			bool		ortho() const;
			Material*	replacementMaterial() const;

			//-----------------

			const glm::mat4& projectionMatrix();
			const glm::mat4& viewMatrix();

			void setup();

			//******************

			static const std::list<Camera*>& cameraList();
			static Camera* current();

		};
	}
}

#endif