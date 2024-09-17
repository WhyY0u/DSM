#include "IfParser.h"

std::string IfParser::getStateBetween() {
	return IfParser::stateBetween;
}

std::vector<Bool> IfParser::split(const std::string& str) {
    int bracketOpen = 0;
    int bracketClose = 0;
    std::vector<Bool> vectorStr;
    std::string strok;

    for (size_t i = 0; i < str.size(); i++) {     
		strok += str[i];   
        if (str[i] == '(') { 
            bracketOpen++;
        }
        
        if (str[i] == ')') {
            bracketClose++;
            std::string trimmed = strok;
            trimmed.erase(std::remove(trimmed.begin(), trimmed.end(), ' '), trimmed.end());
			if(trimmed.find("&") != std::string::npos) {
				trimmed.erase(std::remove(trimmed.begin(), trimmed.end(), '&'), trimmed.end());
			}

		    Bool boool = getParseBool(trimmed);
			
            vectorStr.push_back(boool);
            strok.clear();  
        }
        
        if (str[i] == '&' && i + 1 < str.size() && str[i + 1] == '&') {
             i++;
         }
        
        if (str[i] == '|' && i + 1 < str.size() && str[i + 1] == '|') {
             i++;
        }
    }
    return vectorStr;
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
void IfParser::ParseIfComponent(std::string line, File& file, int countLine) {

	size_t ifs = checkIfEquals(line);
	bool checkIfs = ifs == std::string::npos;
	if (ifs != std::string::npos) {
		if (getStatusParseIF() == StatusParseIF::NotActive) {
			setStatusParseIF(StatusParseIF::Active);
			setIfEditComponent(If());
			setActiveParse(ComponentActiveParse::If);
		}
	}
	if (getActiveParse() == ComponentActiveParse::If) {
		size_t open = line.find("(");
		if (getStatusParseIF() == StatusParseIF::Active) {
			if (open == std::string::npos) {
				bool check = ifs == std::string::npos;
				stateBetween += check + " \n" ? line : line.substr(ifs + 2) + " \n";
			}
			if (open != std::string::npos) {
				if (stateBetween.length() == 0) {
					std::string result = line.substr(ifs + 2, open - ifs - 2);
					if (result.find_first_not_of(" \t") == std::string::npos) {
						setStatusParseIF(StatusParseIF::ActiveConditions);
						stateBetween = "";
					}else {
						file.getErrorManager().addError("Syntax error between if and ( there may only be tabs or spaces: " + RED_COLOR + stateBetween + RESET_COLOR, countLine, ErrorType::Syntax);
						setStatusParseIF(StatusParseIF::NotActive);
						setIfEditComponent(If());
						setActiveParse(ComponentActiveParse::None);
					}
				} else {
					if (stateBetween.find_first_not_of(" \t") == std::string::npos) {
						setStatusParseIF(StatusParseIF::ActiveConditions);
						stateBetween = "";
					}else {
						file.getErrorManager().addError("Syntax error between if and ( there may only be tabs or spaces: " + RED_COLOR + stateBetween + RESET_COLOR, countLine, ErrorType::Syntax);
						setStatusParseIF(StatusParseIF::NotActive);
						setIfEditComponent(If());
						setActiveParse(ComponentActiveParse::None);
					}
				}
			}
		}
		if (getStatusParseIF() == StatusParseIF::ActiveConditions) {
		    	stateBetween += line;
				size_t close = line.find(')', open);
				for(char c : line) {
                    if(c == '(') countOpen+= 1;
					if(c == ')') countClose+=1;
				}
			
			   if(countOpen == countClose) {
				size_t last = stateBetween.rfind(")");
				size_t first = stateBetween.find("(");
				for(Bool boool: split(stateBetween.substr(first + 1, last - first - 1))) {
                    
				}
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

