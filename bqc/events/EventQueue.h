#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <functional>
#include <vector>
#include <deque>
#include <unordered_map>

#include "events/Event.h"

class EventQueue {
public:
	template <typename EventT, typename FunctionT> void addEventListener(FunctionT& callback);
	void sendEvent(Event* evt);
	void processEvents();
	
private:
	std::unordered_map<Event::Type, std::vector<std::function<void(Event*)>>> eventListeners;
	std::deque<Event*> queue;
	template <typename EventT, typename FunctionT>
	static std::function<void(Event*)> eventWrapper(FunctionT func)
	{
		return [=](Event* evt) {
			func(static_cast<EventT*>(evt));
		};
	}
};

template <typename EventT, typename FunctionT> void EventQueue::addEventListener(FunctionT& callback)
{
	eventListeners[EventT::type].push_back(EventQueue::eventWrapper<EventT>(callback));
}

#endif