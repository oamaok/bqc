#include "events/Event.h"

class EngineEvent : public Event 
{
public:
	EVENT_TYPE(Event::ENGINE_EVENT);

	enum Signal {
		SIGNAL_STOP
	};

	Signal signal;

	EngineEvent(Signal signal)
		: signal(signal)
	{
	}
};