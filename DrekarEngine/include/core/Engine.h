#ifndef DE_ENGINE_H
#define DE_ENGINE_H

#include "export.h"
#include "core/AScreen.h"

#include <list>

/**

\namespace de

\brief the namespace of the engine

*/
namespace de
{
	/**
	* \class Engine
	*
	* \brief Main class driving the Engine
	*
	* This class cannot be instantiated. Instead initialize should be used.
	* All the interface is throught static method, a simple use would be 
	*
	* \code
	*     Engine::initialize(800, 600, false);
	*     Engine::loop();//launch the rendering loop, that will call update/draw on all screens
	* \endcode
	*/
	class DE_EXPORT Engine
	{
	protected:
		static Engine* sInstance;

		int		mWidth;
		int		mHeight;
		bool	mFullscreen;

		bool	mRunning;

		std::list<AScreen*> mScreens;
		std::list<AScreen*> mInitScreens;	// screen waiting for initialization
		std::list<AScreen*> mDeleteScreens;

		Engine(int pWidth, int pHeight, bool pFullscreen);

	public:
		static void		initialize(int pWidth = 800, int pHeight = 600, bool pFullscreen = false);
		static void		loop();

		/**
		*	\brief push a screen on the pile, it became the new updated/rendered screen
		*/
		static void		pushScreen(AScreen* pScreen);

		/**
		*	\brief	pop the screen from the pile and return it. if you wish to delete the screen
		*			pass true as argument, this will flag the screen for deletion. Avoid deleting the
		*			screen right away, especialy if it's the current main screen...
		*/
		static AScreen* popScreen();


		static int width();
		static int height();

		~Engine();
	};
}


#endif