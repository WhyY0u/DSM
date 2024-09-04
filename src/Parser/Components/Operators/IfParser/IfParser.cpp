#include "IfParser.h"

std::string IfParser::getStateBetween() {
	return IfParser::stateBetween;
}

void IfParser::setStateBetween(std::string string) {
	IfParser::stateBetween = string;
}

If IfParser::getEditIfComponent() {
	return IfParser::editIfComponent;
}

void IfParser::setIfEditComponent(If ifs) {
	IfParser::editIfComponent = ifs;
}
void IfParser::setStatusParseIF(StatusParseIF state) {
	IfParser::statusParseIF = state;
}
StatusParseIF IfParser::getStatusParseIF() {
	return IfParser::statusParseIF;
}
void IfParser::ParseIfComponent(std::string line) {

	size_t ifs = checkIfEquals(line);
	if (ifs != std::string::npos) {
		if (getStatusParseIF() == StatusParseIF::NotActive) {
			setStatusParseIF(StatusParseIF::Active);
			setIfEditComponent(If());
			setActiveParse(ComponentActiveParse::If);
		}
	}

	if (getStatusParseIF() == StatusParseIF::Active && getActiveParse() == ComponentActiveParse::If) {
		std::cout << stateBetween.length() << std::endl;

		size_t open = line.find("(");
		if (ifs != std::string::npos) {
			if (open != std::string::npos) {
				if (stateBetween.length() == 0) {
					std::string result = line.substr(ifs + 2, open - ifs - 2);
					if (result.find_first_not_of(" \t") == std::string::npos) {

					}
				} else {
					stateBetween += line;
					std::cout << "BetWeen: " << stateBetween << std::endl;
				}
			} else {
				bool check = ifs == std::string::npos;
				stateBetween += check ? line : line.substr(ifs + 2);
			}
		}
	}
}
size_t IfParser::checkIfEquals(std::string line) {
	size_t ifs = line.find("if");
	if (ifs == std::string::npos) return std::string::npos;
	if (getActiveParse() == ComponentActiveParse::None || getActiveParse() == ComponentActiveParse::InsideIF ||getActiveParse() == ComponentActiveParse::If) {
		std::string beforeIf = line.substr(ifs - 1, 1);
		std::string afterIf = line.substr(ifs + 2, 1);
		if ((beforeIf.find_first_not_of(" \t") == std::string::npos || beforeIf.find_first_not_of(";") == std::string::npos) && (afterIf.find_first_not_of(" \t") == std::string::npos || afterIf.find_first_not_of("(") == std::string::npos)) {
			return ifs;
		}
	}
	return std::string::npos;
}

