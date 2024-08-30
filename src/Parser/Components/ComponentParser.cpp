#include "ComponentParser.h"

Component getParseComponent(std::string line, Component component) {
	std::cout << "LINE PARSE: " << line << std::endl;
	return component;
} 

void setParseComponent(Component component, ComponentManager componentManager) {
	Component edit = componentManager.getEditComponent();
	if (edit.getName().empty()) {
		componentManager.setEditComponent(component);
	}
}