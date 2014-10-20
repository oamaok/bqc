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

void Log::_print(const std::string& prefixString, const char* format, va_list args)
{
	
	char *dst = new char[500];
	vsnprintf(dst, 500, format, args);
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	char *time = new char[100];
	snprintf(time, 100, "[%02d:%02d:%02d] %s ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, prefixString.c_str());
	
	char *concatted = new char[600];
	strcpy(concatted, time);
	strcat(concatted, dst);

	util::writeLine("debug.log", std::string(concatted));

	delete [] dst;
	delete [] time;
	delete [] concatted;
}
