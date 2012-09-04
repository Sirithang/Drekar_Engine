#ifndef DE_OGLOBJECT_H
#define DE_OGLOBJECT_H

#include "export.h"

namespace de
{
	/**
	* \brief	this class is the base class allowing to count object.
	*			It take car of tracking the copy, and release the object once not referenced by nothing
	*			The child class must implement a public "release()" function that must clean the object (instead of the destructor)
	*			NOTE : the object is deleted each time, only the function release is called once the count reach zero.
	*/
	template <class T>
	class CountedObject
	{
	protected:
		int*	mNumbers;

		void decreaseCount();

	public:

		CountedObject();
		CountedObject(const CountedObject& pOther);

		CountedObject&	operator=(const CountedObject& pOther);

		~CountedObject();
	};


	//----------IMPLEMENTATION---------------------
	template <class T>
	CountedObject<T>::CountedObject()
	{
		mNumbers = new int;
		*mNumbers = 1;
	}

	template <class T>
	CountedObject<T>::CountedObject(const CountedObject<T>& pOther)
	{
		mNumbers = pOther.mNumbers;
		*mNumbers += 1;
	}

	template <class T>
	CountedObject<T>::~CountedObject()
	{
		decreaseCount();
	}

	template <class T>
	void CountedObject<T>::decreaseCount()
	{
		if(mNumbers == nullptr)
			return;

		*mNumbers -= 1;

		if(*mNumbers == 0)
		{
			((T*)this)->release();
			delete mNumbers;
		}
	}

	//-------------------------

	template <class T>
	CountedObject<T>& CountedObject<T>::operator=(const CountedObject<T>& pOther)
	{
		if(this != &pOther)
		{
			decreaseCount();

			mNumbers = pOther.mNumbers;
			*mNumbers += 1;
		}

		return *this;
	}
}

#endif