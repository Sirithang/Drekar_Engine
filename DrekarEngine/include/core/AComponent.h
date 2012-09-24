#ifndef DE_COMPONENT_H
#define DE_COMPONENT_H

#include "export.h"
#include <string>

namespace de
{
	class GameObject;

	class DE_EXPORT AComponent
	{
	protected:
		GameObject* mOwner;

	public:
		AComponent();

		//-------------------------

		GameObject* owner();

		//-------------------------

		/**
		* \brief called by the gameobject once the component has been had to its component list
		*/
		virtual void init();

		/**
		* \brief called each update
		*/
		virtual void update();

		/**
		* \brief called after update but before rendering
		*/
		virtual void preDraw();

		/**
		* \brief Only called if this component was added to the current renderer ( Renderer::current() )
		*/
		virtual void render();

		/**
		* \brief overriden in each component to parse JSON data from .asset
		*/
		virtual void fromJSON(const std::string& pData);

		friend class GameObject;
	};
}

#endif