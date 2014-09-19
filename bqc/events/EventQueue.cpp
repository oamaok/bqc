#include "events/EventQueue.h"

void EventQueue::processEvents()
{
	while(!queue.empty())
	{
		Event* evt = queue.front();
		queue.pop_front();

		for(auto& listener : eventListeners[evt->getType()])
		{
			listener(evt);
		}

		delete evt;
	}
}

void EventQueue::sendEvent(Event* evt)
{
	queue.push_back(evt);
}
