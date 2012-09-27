#ifndef DE_ARENDERABLE_H
#define DE_ARENDERABLE_H

#include "export.h"
#include <cstdint>
#include <list>

namespace de
{
	class DE_EXPORT ARenderable
	{
	protected:
		static std::list<ARenderable*> sRenderables;

	public:
		ARenderable();
		virtual  ~ARenderable();

		/**
		* \brief override that to define any pre-operation needed befor rendering (like materia setting etc.)
		*/
		virtual void setup() = 0;

		/*
		* \brief override that for actual rendering (like calling draw on a VBO)
		*/
		virtual void render() = 0;

		virtual uint32_t getKey() const = 0;

		static std::list<ARenderable*>& getRenderables();
	};
}

#endif