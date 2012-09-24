#ifndef DE_LIGHT_H
#define DE_LIGHT_H

#include "export.h"
#include "core/AComponent.h"
#include "data/Mesh.h"
#include "core/Program.h"

#include <glm/glm.hpp>

namespace de
{
	namespace component
	{
		/**
		* \brief abstract class for all light type. Just allow to define common properties
		*	     as color, intensity etc... ans stuff
		*/
		class DE_EXPORT Light : public AComponent
		{
		protected:
			float		mIntensity;
			glm::vec3	mColor;

		public:
			Light();

			//---get/set--

			float		intensity() const;
			glm::vec3	color() const;

			void setIntensity(float pValue);
			void setColor(const glm::vec3& pValue);

			//--------

			virtual void init() = 0;

			/**
			* \brief this fonction pass the different information usefull to the shader, according to the light type
			*/
			virtual void setup(Program* pProg) = 0;
		};
	}
}

#endif