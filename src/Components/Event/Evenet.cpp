#include "Evenet.h"

EventType Event::getType() {
	return Event::type;
}

std::vector<Setting> Event::getSettings(){
	return Event::settings;
}

std::string getEventType(EventType type) {
	switch (type)
	{
	case EventType::MOUSE_CLICKED:
		return "onClick()";
		break;
	case EventType::MOUSE_HOVER:
		return "isHover()";
		break;
	case EventType::ACTIVE:
		return "onActive()";
		break;
	default:
		break;
	}
	return "NONE";
}

EventType getEventTypeByString(std::string str) {
	if(str == "onClick()") return EventType::MOUSE_CLICKED;
	if (str == "isHover()") return EventType::MOUSE_HOVER;
	if (str == "onActive()") return EventType::ACTIVE;
	return EventType::NONE;
}
