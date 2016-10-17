#pragma once

#include <initializer_list>
#include <string>

class Logger
{
private:
	Logger();

public:
	Logger(const Logger&) = delete;
	~Logger();

	void operator=(const Logger&) = delete;

	static Logger& GetInstance()
	{
		static Logger instance;
		return instance;
	}

	static void Log(const std::wstring &message, const std::wstring &filename = L"logFile.txt");
	static void Clear(const std::wstring &filename = L"logFile.txt");
};