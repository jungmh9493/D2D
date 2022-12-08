#include "stdafx.h"
#include "Time.h"

Time* Time::instance = nullptr;

Time::Time()
{
	currentTime = chrono::steady_clock::now();
	lastTime = currentTime;
}

Time::~Time() {}

void Time::Update()
{
	currentTime = chrono::steady_clock::now();
	chrono::duration<double> delta = currentTime - lastTime;
	deltaTime = delta.count();

	lastTime = currentTime;
	worldTime += deltaTime;

	fpsTimeElapsed += deltaTime;
	++frameCount;

	if (fpsTimeElapsed > 1.0)
	{
		fps = frameCount;
		frameCount = 0;
		fpsTimeElapsed = 0;

		//CheckTime();
	}
}

