#pragma once
#include <memory>
#include <Windows.h>

class Timer
{
private:
	long long m_frequency, m_previousTime;

	Timer();
public:
	~Timer();

	static bool Init();
	static Timer& GetInstance()
	{ 
		static Timer instance;
		return instance; 
	}

	double Tick();
};
