#ifndef DE_GAMETIME_H
#define DE_GAMETIME_H

#include "export.h"

namespace de
{
	class DE_EXPORT GameTime
	{
	protected:
		static GameTime	sInstance;

		float		mDeltaTime;
		double		mTimeOfLastFrame;
		double		mStartingTime;
		double		mTimeSinceStart;

	public:
		static void init();
		static void tick();
		static float deltaTime();
		static float sinceStart();
	};
}

#endif