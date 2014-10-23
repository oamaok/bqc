#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <cstdarg>
#include "util/util.h"

class Log
{
public:
	static void print(const char* format, ...);
	static void error(const char* format, ...);
	static void warning(const char* format, ...);
private:
	static void _print(const char* prefixString, const char* format, va_list args);
	static const int MAX_LENGTH = 1024;
};

#endif