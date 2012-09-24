#ifndef DE_COMPONENTFACTORY_H
#define DE_COMPONENTFACTORY_H

#include "export.h"
#include "AComponent.h"

#include <string>
#include <map>

namespace de
{
	template<typename T> AComponent* createT() { return new T; }

	class DE_EXPORT ComponentFactory
	{
	public:
		typedef std::map<std::string, AComponent*(*)()> map_type;

		static AComponent * createInstance(std::string const& s) {
			map_type::iterator it = getMap()->find(s);
			if(it == getMap()->end())
				return 0;
			return it->second();
		}

		protected:
			static map_type * getMap() {
				if(map == nullptr) { map = new map_type; } 
				return map; 
			}

		private:
			static map_type* map;
	};

	template<typename T>
	struct DerivedRegister : ComponentFactory 
	{ 
		DerivedRegister(std::string const& s) { 
			getMap()->insert(std::make_pair(s, &createT<T>));
		}
	};
}

///*********  MACRO FOR COMPONENT DERIVATED REGISTERING *****

#define COMPONENT_DEC_TYPE(NAME) \
    static de::DerivedRegister<NAME> reg

#define COMPONENT_DEF_TYPE(NAME) \
    de::DerivedRegister<NAME> NAME::reg(#NAME)

//**********************************************************

#endif