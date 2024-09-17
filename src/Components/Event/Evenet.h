#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include "../Settings/Settings.h"
#include <vector>

enum class EventType {
	MOUSE_CLICKED,
	MOUSE_HOVER,
	ACTIVE,
	NONE,
};
enum class StatusEvent {
    Active,
	NoActive
};

std::string getEventType(EventType type);
EventType getEventTypeByString(std::string str);
class Event {
public:
	EventType getType();
	void setType(EventType type);
	StatusEvent getStatusEvent();
	void setStatusEvent(StatusEvent event);
private:
	EventType type;
	StatusEvent statusEvent;
};
#endif 