#ifndef DE_GAMEOBJECT_H
#define DE_GAMEOBJECT_H

#include "export.h"
#include "AComponent.h"
#include "component/Transform.h"

#include <string>
#include <list>

namespace de
{
	class DE_EXPORT GameObject
	{
	private:
		//Keep all GameObject Listed. A GameObject is added to this list once created. If it's made son of ny other gameObject, it's
		//removed from the list (as it's parent will take care of updating him)
		static std::list<GameObject*> sGameObjects;

		void internalUpdate();	//this is called only by Engine, cannot be derived
		void internalDraw();	//this is called only by Engine, cannot be derived

	protected:
		std::list<AComponent*>	mComponents;
		component::Transform*	mTransform; // shortcut to the component transform

		std::string				mName;
		bool					mActive;

	public:
		GameObject(std::string pName = "GameObject");

		virtual ~GameObject();

		/**
		* \brief	override this to implement per-frame behavior.
		*			It's called before interalUpdate, mean that component get updated AFTER this.
		*			This allow to modify their values and see this repercuted this frame.)
		*			
		*			Remember to call GameObject::update() in your subclass to allow update in you derived child to be called!
		*/
		virtual void update();

		/**
		* \brief override this to define  a behaviour just before drawing
		*
		*		Remember to call GameObject::draw() in your subclass to allow draw in you derived child to be called!
		*/
		virtual void draw();


		virtual void fromAsset(const std::string pFile);

		/**
		* \brief add a component to the gameobject
		*		 return the component passed as argument for chaining
		*/
		AComponent* addComponent(AComponent* pComponent);

		/**
		* \brief simply a shortcut to the transform component of this GameObject
		*/
		component::Transform* transform() { return mTransform; }

		friend class AScreen;
	};
}




#endif