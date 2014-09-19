#include "events/EventQueue.h"



void EventQueue::processEvents()
{
	while(!queue.empty())
	{
		const Event* evt = queue.front();
		queue.pop_front();

		for(auto& listener : eventListeners[evt->getType()])
		{
			listener(evt);
		}
	}
}

void EventQueue::sendEvent(const Event* evt)
{
	queue.push_back(evt);
}
