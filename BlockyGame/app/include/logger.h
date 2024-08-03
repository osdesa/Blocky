#pragma once
#include "defines.h"
#include <fstream>
#include <cstdarg>

enum error_levels{ FATAL = 0, CRITICAL = 1, WARNING = 2, VALIDATION = 3, KEYINFO = 4 ,INFO = 5 };

class Logger
{
private:
	const char* filepath = 0;
	std::fstream logFile;

	Logger() {}
	Logger(const Logger&) = delete;
	Logger& operator= (const Logger&) = delete;
	static Logger& get_instance();

public:
	static void init(const char* filePath);

	static void output(error_levels level, const char* msg,...);
	static void shutdown();
};
