#pragma once

#include <initializer_list>
#include <string>

class Logger
{
public:
	static void Log(const std::wstring &message);
	static void Clear();
private:
	Logger() { }
};