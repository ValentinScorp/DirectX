/*
 * Clock.cpp
 *
 *  Created on: 23 но€б. 2017 г.
 *      Author: Valentin.Bloschinski
 */

#include "Clock.h"

Clock::Clock()
{
	QueryPerformanceFrequency(&frequency);
	performanceCounter = frequency;
	elapsedTimeSec = 0.1f;
}

Clock::~Clock()
{
}

void Clock::Update()
{
	LARGE_INTEGER performanceCounterCurrent;
	QueryPerformanceCounter(&performanceCounterCurrent);
	__int64 diff = performanceCounterCurrent.QuadPart - performanceCounter.QuadPart;
	__int64 freq = frequency.QuadPart;
	if (diff != 0 && freq != 0) {
		elapsedTimeSec = (1.0f / (float)freq) * diff;
	}
	performanceCounter = performanceCounterCurrent;
}

float Clock::GetDeltaTime()
{
	return elapsedTimeSec;
}

