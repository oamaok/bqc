#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <functional>
#include <vector>
#include <deque>
#include <unordered_map>

#include "events/Event.h"


class EventQueue {
public:
	template <typename T, typename F> void addEventListener(F& callback);
	void sendEvent(const Event* evt);
	void processEvents();
	
private:
	std::unordered_map<Event::Type, std::vector<std::function<void(const Event*)>>> eventListeners;
	std::deque<const Event*> queue;
	template <typename EventT, typename FunctionT>
	static std::function<void(const Event*)> eventWrapper(FunctionT func)
	{
		return [=](const Event* evt) {
			func(static_cast<const EventT*>(evt));
		};
	}

};


template <typename EventT, typename FunctionT> void EventQueue::addEventListener(FunctionT& callback)
{
	eventListeners[EventT::type].push_back(EventQueue::eventWrapper<EventT>(callback));
}


#endif