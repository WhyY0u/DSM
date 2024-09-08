#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include "../Settings/Settings.h"

enum class EventType {
	MOUSE_CLICKED,
	MOUSE_HOVER,
	ACTIVE,
	NONE,
};
std::string getEventType(EventType type);
class Event {

public:
	EventType getType();
	std::vector<Setting> getSettings();

private:
	EventType type;
	std::vector<Setting> settings;
};
#endif // !EVENT_H