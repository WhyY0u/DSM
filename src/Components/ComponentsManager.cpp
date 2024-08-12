#include "ComponentsManager.h"

enum class ComponentType {
	Unknown,
	Square,
};
struct Value {
	std::string name;
	std::unordered_map<std::string, std::variant<int, float, double, bool, std::string>> value;
};
ComponentType getComponentFromString(const std::string& str) {
	if (str == "Square") return ComponentType::Square;
	return ComponentType::Unknown;
}

Component ComponentManager::getEditComponent() {
	return editComponent;
}

std::vector<Value> Component::getValue() {
	return Component::value;
}
