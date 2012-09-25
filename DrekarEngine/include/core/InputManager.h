#ifndef DE_INPUTMANAGER_H
#define DE_INPUTMANAGER_H

#include "export.h"

#include <map>

namespace de
{
	namespace io
	{
		class AInput;
	}

	class Engine;

	class DE_EXPORT InputManager
	{
	protected:
		static InputManager* sInstance;
		
		std::map<std::string, io::AInput*> mInputs;

		static void init();

		friend class de::Engine;
	public:

		/**
		* \brief this is called by the engine, althought if you need immediate axis update, call it explicitly.
		*/
		static void			update();

		/**
		* \brief return nullptr if can't find the input BEWARE : since the order isn't known in the Input list, it always return the first one of this type it found. 
		*/
		static io::AInput*	getInputFromType(const std::string& pType);

		/**
		* \brief return nullptr if can't find the input
		*/
		static io::AInput*	getInputFromName(const std::string& pName);

		/**
		* \brief	This return the added input, to chain easily, or add and retrieve in one go. 
		*			NOTE: Usually not usefull, the simple fact of instanciating an Input source add it to the manager.
		*/
		static io::AInput*	addInputSource(io::AInput* pInput);
		static void			removeInputSource(io::AInput* pInput);
	};
}

#endif