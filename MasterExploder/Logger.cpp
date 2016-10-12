#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Logger.h"

void Logger::Log(const std::wstring &message)
{
	std::wofstream logFile;
	logFile.open("logFile.txt", std::ios_base::app);

	auto t = std::time(nullptr);
	struct tm timeinfo;
	localtime_s(&timeinfo, &t);

	logFile << std::put_time(&timeinfo, L"%d-%m-%Y %H:%M:%S") << " : " << message << std::endl;

	logFile.close();
}

void Logger::Clear()
{
	std::ofstream ofs;
	ofs.open("logFile.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}