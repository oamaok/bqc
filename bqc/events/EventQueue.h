#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <functional>
#include <vector>

#include "events/Event.h"


struct EventListener {
	Event::Type type;
	std::function<void(Event evt)> callback;
};

class EventQueue {
public:
	void addEventListener(Event::Type type, std::function<void(Event evt)> callback);
	void pushEvent(Event evt);
	void processEvents();
	
private:
	std::vector<EventListener> eventListeners;
	std::vector<Event> queue;
};


#endif