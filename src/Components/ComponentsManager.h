#ifndef COMPONENTS_H
#include <string>
#include <variant>
#include <unordered_map>
#include <vector>

#define COMPONENTS_H

enum class ComponentType;
struct Value;
ComponentType getComponentFromString(const std::string& str);

class Component {

public:
	std::vector<Value> getValue();
private:
	ComponentType type;
	std::vector<Value> value;
};

class ComponentManager {

public:

  Component getEditComponent();

private:
   Component editComponent;
};

#endif