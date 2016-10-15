#pragma once
#include <memory>
#include <Windows.h>

class Timer
{
private:
	static std::shared_ptr<Timer> m_instance;

	long long m_frequency, m_previousTime;

public:
	//MKOS: TODO private
	Timer();
	~Timer();

	static bool Init();
	static std::shared_ptr<Timer> GetInstance() { return m_instance; }

	double Tick();
};
