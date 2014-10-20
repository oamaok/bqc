#include <string>
#include <cstdarg>
#include "util/util.h"

class Log
{
public:
	static void print(const char* format, ...);
	static void error(const char* format, ...);
	static void warning(const char* format, ...);
};