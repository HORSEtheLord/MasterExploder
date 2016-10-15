#include  "Timer.h"

Timer::Timer()
{
	LARGE_INTEGER t;

	QueryPerformanceFrequency(&t);
	m_frequency = t.QuadPart;

	QueryPerformanceCounter(&t);
	m_previousTime = t.QuadPart;
}

Timer::~Timer()
{
}

Timer* Timer::m_instance = nullptr;

bool Timer::Init()
{
	m_instance = new Timer();
	return true;
}

double Timer::Tick()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	long long currentTime = t.QuadPart;
	double elapsedTime = currentTime - m_previousTime;
	m_previousTime = currentTime;
	double lag = 1000 * elapsedTime / m_frequency;
	return lag;
}


