#include "events/Event.h"
#include <string>

class PrintEvent : public Event 
{
public:

	std::string data;

	static const Type type = Event::PRINT_EVENT;
	Event::Type getType() const { return type; }

	PrintEvent(const std::string& data)
		: data(data)
	{
	}

};