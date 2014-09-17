#include "events/EventQueue.h"

void EventQueue::addEventListener(Event::Type type, std::function<void(Event evt)> callback)
{
	EventListener listener = {type, callback};
	eventListeners.push_back(listener);
}

void EventQueue::processEvents()
{
	Event evt;
	while(!queue.empty())
	{
		evt = queue.front();
		queue.erase(queue.begin());

		for(EventListener listener : eventListeners)
		{
			if(listener.type == evt.type)
			{
				listener.callback(evt);
			}
		}
	}
}

void EventQueue::pushEvent(Event evt)
{
	queue.push_back(evt);
}