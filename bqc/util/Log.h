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
	static void _print(const std::string& prefixString, const char* format, va_list args);
};