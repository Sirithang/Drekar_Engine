#ifndef DE_GAMEOBJECT_H
#define DE_GAMEOBJECT_H

#include "export.h"
#include "CountedObject.h"
#include "AComponent.h"
#include "component/Transform.h"

#include <string>
#include <list>

namespace de
{
	class DE_EXPORT GameObject : public CountedObject<GameObject> 
	{
	private:
		static std::list<GameObject*> sGameObjects; // keep track of all gameObject created and deleted. A GameObject start to be a part of the games once created

		void internalUpdate();	//this is called only by Engine, cannot be derived
		void internalDraw();	//this is called only by Engine, cannot be derived

	protected:
		GameObject*				mParent;
		std::list<GameObject*>	mChildren;

		std::list<AComponent*>	mComponents;
		component::Transform*	mTransform; // shortcut to the component transform

		bool					mActive;

	public:
		GameObject();
		GameObject(std::string pName);

		void release();

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

		/**
		* \brief add a component to the gameobject
		*		 return the component passed as argument for chaining
		*/
		AComponent* addComponent(AComponent* pComponent);

		void addChild(GameObject* pChild);

		/**
		* \brief simply a shortcut to the transform component of this GameObject
		*/
		component::Transform* transform() { return mTransform; }

		friend class AScreen;
	};
}




#endif