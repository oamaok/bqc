#include "util/config.h"

#include "events/EventQueue.h"
#include "events/PrintEvent.h"

#include <stdio.h>

EventQueue gEventQueue;

void testListener(const PrintEvent* evt)
{
	printf(evt->data.c_str());
}

int main(void)
{

	gEventQueue.addEventListener<PrintEvent>(testListener);

	PrintEvent asd("ebin");

	gEventQueue.sendEvent(&asd);
	gEventQueue.processEvents();

	getchar();

	return 0;
}