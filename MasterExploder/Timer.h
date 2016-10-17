#pragma once
#include <memory>
#include <Windows.h>

class Timer
{
private:
	long long m_frequency, m_previousTime;

public:
	Timer();
	Timer(const Timer&) = delete;
	~Timer();

	void operator=(const Timer&) = delete;

	double Tick();
};
