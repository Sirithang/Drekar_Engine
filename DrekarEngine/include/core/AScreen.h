#ifndef DE_ASCREEN_H
#define DE_ASCREEN_H

#include "export.h"
#include "Gameobject.h"
#include "renderer/Renderer.h"


namespace de
{
	/**
	* \brief This class define a screen. Subclass this to define the screens needed for your game.
	*		 A screen is composed of a tree of object (the scene), and a GUI Layer. Screen are
	*		 pushed into the screen pile of the Engine. the engine always render/update the 
	*        screen at the top of the pile.
	*/
	class DE_EXPORT AScreen
	{
	private:
		//called by engine, cannot be override. Update allg GameObject;
		void internalUpdate();
		//called by engine, cannot be override. Draw all GameObject;
		void internalDraw();

	protected:
		renderer::Renderer	mRenderer;

	public:
		virtual void init();

		/**
		 *\brief this is called once per frame. It'scalled BEFORE the internal update (and so before the "update" and "internalUpdate" of all GameObject. Set per-frame data here
		 */
		virtual void update();
		
		/**
		 *\brief tis is called before drawing. But before internalDraw (and so before "draw" and "internalDraw" of all GameObject")
		 */
		virtual void draw();

		friend class Engine;
	};
}

#endif