#ifndef SOURCE_CLOCK_H_
#define SOURCE_CLOCK_H_

#include "Precompiled.h"

class Clock
{
private:
	LARGE_INTEGER performanceCounter;
	LARGE_INTEGER frequency;
	float elapsedTimeSec;

public:
	Clock();
	~Clock();

	void Update();
	float GetDeltaTime();
};

#endif /* SOURCE_CLOCK_H_ */
