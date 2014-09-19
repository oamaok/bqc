#ifndef EVENT_H_
#define EVENT_H_

class Event {
public:
	enum Type {
		BASE_EVENT,
		PLAYER_EVENT,
		TILE_EVENT,
		PRINT_EVENT
	};
	virtual ~Event(){};
	virtual Event::Type getType() const = 0;
};

#endif