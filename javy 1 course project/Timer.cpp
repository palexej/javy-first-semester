#include "pch.h"
#include "Timer.h"



Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

Timer::~Timer()
{
}

void Timer::start()
{
	//запуск таймера
	mStarted = true;

	//убрать паузу таймера
	mPaused = false;

	//получение текущего времени таймера
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//остановить таймер
	mStarted = false;

	///убрать паузу таймера
	mPaused = false;

	//сброс времени
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	
	//если таймер запущен и не остановлен
	if (mStarted && !mPaused)
	{
		mPaused = true;

		//рассчёт времени паузы
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//если таймер запущен и на паузе
	if (mStarted && mPaused)
	{

		mPaused = false;

		//сброс начального значения таймера
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//сброс времени паузы
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;

	if (mStarted)
	{
	
		if (mPaused)
		{
			//получаем время паузы таймера
			time = mPausedTicks;
		}
		else
		{
			//текущее время минус начальное
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//таймер запущен
	return mStarted;
}

bool Timer::isPaused()
{
	//таймер запущен и остановлен
	return mPaused && mStarted;
}
