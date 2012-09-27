#ifndef DE_MESHRENDERER_H
#define DE_MESHRENDERER_H

#include "core/AComponent.h"
#include "core/ARenderable.h"
#include "core/Material.h"
#include "core/ComponentFactory.h"
#include "data/Mesh.h"


namespace de
{
	namespace component
	{
		class DE_EXPORT MeshRenderer : public AComponent, public ARenderable
		{
		protected:

			Material*	mMaterial;
			data::Mesh*	mMesh;

			COMPONENT_DEC_TYPE(MeshRenderer);

		public:


			/**
			* \brief this actually setup the material. Call once for each batch.
			*/
			void setup();

			/**
			* \brief This doesn't setup the material, only the needed info (world) call getMaterial()->setup() if you're doing it by hand.
			*/
			void render();

			void init();

			void fromJSON(const std::string& pData);

			uint32_t getKey() const;

			void setMesh(data::Mesh* pMesh);
			void setMaterial(Material* pMaterial);

			de::Material* getMaterial();
		};
	}
}

#endif