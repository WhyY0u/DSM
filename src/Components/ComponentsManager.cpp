#include "ComponentsManager.h"

ComponentType getComponentFromString(const std::string& str) {
	if (str == "Square") return ComponentType::Square;
	return ComponentType::Unknown;
}

std::string getStringFromComponent(const ComponentType type) {
	if (type == ComponentType::Square) return "Square";
	return "NULL";
}

Component ComponentManager::getEditComponent() {
	return ComponentManager::editComponent;
}

void ComponentManager::setEditComponent(Component component) {
	ComponentManager::editComponent = component;
}

void ComponentManager::newEditComponent() {
	ComponentManager::editComponent = Component();
}

std::vector<Setting> Component::getSettings() {
	return Component::settings;
}

ComponentType Component::getType() {
	return Component::type;
}

std::string Component::getName() {
	return Component::name;
}

void Component::setType(ComponentType type) {
	Component::type = type;
}

void Component::setName(std::string name) {
	Component::name = name;
}

std::vector<Event> Component::getEvents(){
	return Component::events;
}
