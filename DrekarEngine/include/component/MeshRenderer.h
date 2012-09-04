#ifndef DE_MESHRENDERER_H
#define DE_MESHRENDERER_H

#include "core/AComponent.h"
#include "core/Material.h"
#include "data/Mesh.h"

namespace de
{
	namespace component
	{
		class DE_EXPORT MeshRenderer : public AComponent
		{
		protected:
			Material*	mMaterial;
			data::Mesh	mMesh;

		public:
			void render();
			void init();

			void setMesh(data::Mesh& pMesh);
			void setMaterial(Material* pMaterial);
		};
	}
}

#endif