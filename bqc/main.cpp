#include "json/Json.h"
#include "util/Config.h"

#include "events/EventQueue.h"
#include "events/PrintEvent.h"
#include "events/EngineEvent.h"

#include "util/Log.h"
#include "tiles/Tileset.h"

#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

EventQueue gEventQueue;


int main(void)
{
	// only test cases so far, ignore/modify as you like

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
		printf("%d\n", Config::get<int>("map.width"));
		Tileset ts("core");
		for(const auto& name : ts.getTileNames())
		{
			printf("%s\n", name.c_str());
		}
		getchar();
		gEventQueue.sendEvent(stop);
		gEventQueue.processEvents();
	}

	return 0;
}
