#ifndef IFPARSER_H
#define IFPARSER_H
#include <string>
#include "If.h"
#include "ComponentParserUtils.h"
#include "Evenet.h"
#include "FileManager.h"
#include "Bool.h"
#include "ErrorUtils.h"
#include "BoolParser.h"
#include <regex>

enum class StatusParseIF {
	Active,
	AddSettings,
	NotActive,
	ActiveConditions,
	
};
class IfParser {

 public:
	 void setStatusParseIF(StatusParseIF state);
	 void setIfEditComponent(If ifs);
	 StatusParseIF getStatusParseIF();
	 std::string getStateBetween();
	 void setStateBetween(std::string string);
	 std::string getParseIfFromEnum(StatusParseIF parseif) {
		 switch (parseif) {
		 case StatusParseIF::Active:
			 return "Active";
			 break;
		 case StatusParseIF::AddSettings:
			 return "AddSettings";
			 break;
		 case StatusParseIF::NotActive:
			 return "NotActive";
			 break;
		 case StatusParseIF::ActiveConditions:
			 return "ActiveConditions";
			 break;
		 default:
			 return "NULL";
			 break;
		 }
	 }
	 size_t checkIfEquals(std::string line);
	 If getEditIfComponent();
    std::vector<Bool> split(const std::string& str);
	 void ParseIfComponent(std::string line, File& file, int countLine);
 private:
	 std::string stateBetween;
	 StatusParseIF statusParseIF = StatusParseIF::NotActive;
     int countOpen = 0, countClose = 0;
	 If editIfComponent;

};

#endif // !IFPARSER_H
