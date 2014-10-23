#include <ctime>
#include <cstdio>

#include "util/Log.h"
#include "util/Util.h"

// visual studio doesn't support snprintf, but has _snprintf instead, how convinient!
#ifdef _MSC_VER
	#define snprintf _snprintf
#endif

void Log::print(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	_print("", format, args);
	va_end(args);
}

void Log::error(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	_print("[ERROR]", format, args);
	va_end(args);
}

void Log::warning(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	_print("[WARNING]", format, args);
	va_end(args);
}

void Log::_print(const char* prefixString, const char* format, va_list args)
{
	char buffer[Log::MAX_LENGTH];
	char *ptr = buffer;

	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime(&rawtime);

	ptr += snprintf(ptr, Log::MAX_LENGTH - (ptr - buffer), "[%02d-%02d-%04d %02d:%02d:%02d] %s ",
		timeinfo->tm_mday, timeinfo->tm_mon, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, prefixString);
	ptr += vsnprintf(ptr, Log::MAX_LENGTH - (ptr - buffer), format, args);

	util::writeLine("debug.log", std::string(buffer));
}
