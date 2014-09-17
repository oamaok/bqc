#ifndef EVENT_H_
#define EVENT_H_

class Event {
public:
	enum Type {
		PLAYER_EVENT,
		TILE_EVENT,
	};

	Type type;


};

#endif