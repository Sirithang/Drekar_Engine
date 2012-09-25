#ifndef DE_TRANSFORM_H
#define DE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

#include "core/AComponent.h"
#include "core/ComponentFactory.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT Transform : public AComponent
		{
		protected:
			COMPONENT_DEC_TYPE(Transform);

			glm::vec3 mPosition;
			glm::vec3 mLocalPosition;
			
			glm::quat mRotation;
			glm::quat mLocalRotation;

			glm::vec3 mLocalScale;

			glm::mat4x4 mMatrix;
			glm::mat4x4 mCombinedMatrix;

			bool	  mChanged;
			bool	  mRecomputed;

			Transform*				mParent;
			std::list<Transform*>	mChildren;

			void parentChanged();

		public:
			Transform();

			void update();

			/**
			* \brief this return true if the transform was recomputed this frame.
			*		 As Transform is always the first to be updated, this allow other component
			*		 to know if the gameObject was moved or changed in any manner
			*/
			bool recomputed() const;

			//-----getter setter

			void setPosition(const glm::vec3& pPosition);
			void setLocalPosition(const glm::vec3& pPosition);
			void setRotation(const glm::quat& pRotation);
			void setScale(const glm::vec3 pScale);

			glm::vec3 forward() const;
			glm::vec3 up() const;
			glm::vec3 left() const;

			const glm::vec3& position();
			const glm::quat& rotation();
			const glm::vec3& scale();

			//-----------------

			/**
			* \brief return the matrix combining all transformation
			*/
			glm::mat4 matrix() const;

			void setParent(Transform* pParent);

			void recomputeMatrix();
		};
	}
}

#endif