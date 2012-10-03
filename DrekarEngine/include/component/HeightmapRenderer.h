#ifndef DE_HEIGHTMAPRENDERER_H
#define DEËHEIGHTMAPRENDERER_H

#include "export.h"
#include "core/AComponent.h"
#include "core/ARenderable.h"
#include "core/Material.h"
#include "core/ComponentFactory.h"
#include "data/Mesh.h"
#include "data/HeightmapInfo.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT HeightmapRenderer : public AComponent, public ARenderable
		{
		protected:
			de::Material*	mMaterial;
			de::data::Mesh*	mMesh;

			data::HeightmapInfo mInfo;

			COMPONENT_DEC_TYPE(HeightmapRenderer);

		public:

			void setup();
			void render();

			uint32_t getKey() const;

			void fromJSON(const std::string& pData);
			void buildFromInfo();
		};
	}
}

#endif