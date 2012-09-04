#ifndef DE_CAMERA_H
#define DE_CAMERA_H

#include "core/AComponent.h"

#include <list>
#include <glm/glm.hpp>

namespace de
{
	namespace component
	{
		class DE_EXPORT Camera : public AComponent
		{
		protected:
			static std::list<Camera*> sCameraList;
			static Camera* sCurrent; // currently used camera

			glm::mat4 mProjection;
			glm::mat4 mView;

			float		mFov;
			float		mAspect;
			glm::vec2	mClipPlanes;

			bool		mRecomputeProjecton;

			void computeProjection();

		public:
			void init();
			void update();

			void release();

			//----getter/setter

			void setFov(float pFov);
			void setAspect(float pAspect);
			void setClipPlane(glm::vec2& pClipPlane);

			float fov() const;

			//-----------------

			const glm::mat4& projectionMatrix();
			const glm::mat4& viewMatrix();

			void setup();

			//**

			static const std::list<Camera*>& cameraList();
			static Camera* current();

		};
	}
}

#endif