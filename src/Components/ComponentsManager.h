#ifndef COMPONENTS_H
#include <string>
#include <variant>
#include <unordered_map>
#include <vector>
#include "Event/Evenet.h"
#define COMPONENTS_H

enum class ComponentType {
	Unknown,
	Square,
};

ComponentType getComponentFromString(const std::string& str);
std::string getStringFromComponent(const ComponentType type);


class Component {
public:
	std::vector<Setting> getSettings();
	ComponentType getType();
	std::string getName();
	void setType(ComponentType type);
	void setName(std::string name);
	std::vector<Event> getEvents();
private:
	ComponentType type;
	std::vector<Setting> settings;
	std::string name;
	std::vector<Event> events;
};




#endif