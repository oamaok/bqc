#include "util/config.h"

#include "events/EventQueue.h"
#include "events/PrintEvent.h"
#include "events/EngineEvent.h"

#include <stdio.h>

EventQueue gEventQueue;


int main(void)
{
	bool running = true;

	gEventQueue.addEventListener<EngineEvent>([&](EngineEvent* evt){
		if(evt->signal == EngineEvent::SIGNAL_STOP)
		{
			running = false;
		}
	});
	
	EngineEvent* stop = new EngineEvent(EngineEvent::SIGNAL_STOP);

	while(running)
	{
		char a = getchar();
		if(a == 'a')
			gEventQueue.sendEvent(stop);

		gEventQueue.processEvents();
	}

	return 0;
}
