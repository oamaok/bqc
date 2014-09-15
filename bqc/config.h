#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include "json\parser.h"

class Config
{
public:
	template<typename T> static T get(std::string key);
private:
	static void init();
};

#endif