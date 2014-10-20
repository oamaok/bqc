#include "json/Json.h"
#include "util/Config.h"

#include "events/EventQueue.h"
#include "events/PrintEvent.h"
#include "events/EngineEvent.h"
#include "util/Log.h"
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

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
		
		auto children = Json::getChildNames("cfg/tiles.json", "gravity");
		for(auto child : children)
		{
			printf("%s\n", child.c_str());
		}
		Log::print("kekkonen");
		Log::error("%d", 20);
		Log::warning("fagerholm");
		
		getchar();
		gEventQueue.sendEvent(stop);
		gEventQueue.processEvents();
	}

	return 0;
}
