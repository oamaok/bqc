#include <ctime>
#include <cstdio>

#include "util/Log.h"
#include "util/Util.h"

void Log::print(const char* format, ...)
{
	char dst[500];
	va_list args;
    va_start(args, format);
	vsnprintf(dst, 500, format, args);
    va_end(args);
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	char time[32];

	// too bad visual studio doesn't support snprintf, must prefix with an underscore!
	// same with the other two cases of the function call.
	_snprintf(time, 32, "[%02d:%02d:%02d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	
	char concatted[532];
	strcpy(concatted, time);
	strcat(concatted, dst);

	util::writeLine("debug.log", std::string(concatted));
}

void Log::error(const char* format, ...)
{
	char dst[500];
	va_list args;
    va_start(args, format);
	vsnprintf(dst, 500, format, args);
    va_end(args);
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	char time[32];
	_snprintf(time, 32, "[%02d:%02d:%02d] [ERROR] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	
	char concatted[532];
	strcpy(concatted, time);
	strcat(concatted, dst);

	util::writeLine("debug.log", std::string(concatted));
}

void Log::warning(const char* format, ...)
{
	char dst[500];
	va_list args;
    va_start(args, format);
	vsnprintf(dst, 500, format, args);
    va_end(args);
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	char time[32];
	_snprintf(time, 32, "[%02d:%02d:%02d] [WARNING] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	
	char concatted[532];
	strcpy(concatted, time);
	strcat(concatted, dst);

	util::writeLine("debug.log", std::string(concatted));
}
