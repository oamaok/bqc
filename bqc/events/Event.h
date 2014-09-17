#ifndef EVENT_H_
#define EVENT_H_

class Event {
	
	enum Type {
		PLAYER_SWITCH_GRAVITY,
		PLAYER_KILL,
		TILE_UPDATE,
	};

	Type type;


};

#endif