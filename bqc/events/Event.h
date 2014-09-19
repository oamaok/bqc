#ifndef EVENT_H_
#define EVENT_H_

#define EVENT_TYPE(TYPE) static const Type type = (TYPE); \
Event::Type getType() const { return type; };

class Event {
public:
	enum Type {
		BASE_EVENT,
		ENGINE_EVENT,
		PLAYER_EVENT,
		TILE_EVENT,
		PRINT_EVENT
	};
	virtual ~Event(){};
	virtual Event::Type getType() const = 0;
};

#endif