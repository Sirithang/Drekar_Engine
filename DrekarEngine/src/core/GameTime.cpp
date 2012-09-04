#include "core/GameTime.h"
#include <time.h>

using namespace de;

GameTime GameTime::sInstance;

void GameTime::init()
{
	sInstance.mStartingTime = (double)clock()/CLOCKS_PER_SEC;
	sInstance.mTimeOfLastFrame = sInstance.mStartingTime;
	sInstance.mTimeSinceStart = 0;
	sInstance.mDeltaTime = 0;
}

void GameTime::tick()
{
	double ltime = (double)clock()/CLOCKS_PER_SEC;

	sInstance.mDeltaTime = ltime - sInstance.mTimeOfLastFrame;
	sInstance.mTimeOfLastFrame = ltime;

	sInstance.mTimeSinceStart += sInstance.mDeltaTime;
}

float GameTime::deltaTime()
{
	return sInstance.mDeltaTime;
}