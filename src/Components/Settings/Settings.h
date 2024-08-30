#ifndef Settings
#define Settings
#include <string>
#include <unordered_map>
#include <variant>

struct Setting {
	std::string name;
	std::unordered_map<std::string, std::variant<int, float, double, bool, std::string>> value;
};
#endif // !Settings

