#ifndef DE_LIGHT_H
#define DE_LIGHT_H

#include "export.h"
#include "core/AComponent.h"
#include "data/Mesh.h"
#include "data/Texture2D.h"
#include "core/Program.h"

#include <map>

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
		public:
			typedef std::multimap<unsigned char, Light*> multimap_t;

		protected:
			//Light are ordered by type (uchar), this allow for differentiation when rendering
			static multimap_t sLights;


			float			mIntensity;
			glm::vec3		mColor;
			unsigned char	mType;

			multimap_t::iterator mIterator;//stocking it for qucik erasing

			void internalSetup(Program* pProg);

		public:
			Light(unsigned char pType);
			virtual ~Light();

			//---get/set--

			float		intensity() const;
			glm::vec3	color() const;

			void setIntensity(float pValue);
			void setColor(const glm::vec3& pValue);

			static multimap_t& getLights();

			//--------

			virtual void init() = 0;

			/**
			* \brief	this function need to be called ony to the first light of the type renderered, it setup all common ifno to this type
			*/
			virtual void setupLightType(de::data::Texture* pAlbedo, de::data::Texture* pNormal, de::data::Texture* pDepth) = 0;

			/**
			* \brief this fonction pass the different information usefull to the shader, according to the light type
			*/
			virtual void setup() = 0;

			/**
			* \brief this functon will be called when the shadowmap is needed to be computed for this light.
			*/
			virtual void renderShadowmap() = 0;
		};
	}
}

#endif