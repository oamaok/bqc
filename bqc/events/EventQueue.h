#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <functional>
#include <map>

#include "events/Event.h"

class EventQueue {
public:
	void addEventListener(Event::Type type, std::function<void> callback);
	
private:

};


#endif