#pragma once
#include <Windows.h>

class Timer
{
private:
	static Timer *m_instance;

	long long m_frequency, m_previousTime;

	Timer();
public:
	~Timer();

	static bool Init();
	static Timer* GetInstance() { return m_instance; }

	double Tick();
};
