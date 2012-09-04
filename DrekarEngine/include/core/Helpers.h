#ifndef DE_HELPERS_H
#define DE_HELPERS_H

#include "export.h"

#include "core/Engine.h"
#include "data/Mesh.h"

namespace de
{
	/**
	* \brief this class contains some helping function like drawing fullscreen quad and stuff
	*/
	class DE_EXPORT Helpers
	{
	protected:
		static Helpers *sInstance;
		
		de::data::Mesh mFullscreenQuad;

		Helpers();
	
	public:

		/**
		* \brief Draw a quad having coordinate (-1, -1, 0) to (1, 1, 0). Combined with the right material, this make a fine fullscreen quad.
		*/
		static void drawQuad();

		friend class de::Engine;
	};
}

#endif