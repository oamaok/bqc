#include "events/Event.h"
#include <string>

class PrintEvent : public Event 
{
public:
	EVENT_TYPE(Event::PRINT_EVENT)


		
	std::string data;
	PrintEvent(const std::string& data)
		: data(data)
	{
	}

};