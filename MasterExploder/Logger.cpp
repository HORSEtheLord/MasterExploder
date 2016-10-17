#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}



void Logger::Log(const std::wstring &message, const std::wstring &filename)
{
	std::wofstream logFile;
	logFile.open(filename, std::ios_base::app);

	auto t = std::time(nullptr);
	struct tm timeinfo;
	localtime_s(&timeinfo, &t);

	logFile << std::put_time(&timeinfo, L"%d-%m-%Y %H:%M:%S") << " : " << message << std::endl;

	logFile.close();
}

void Logger::Clear(const std::wstring &filename)
{
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}