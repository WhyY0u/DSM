#ifndef IFPARSER_H
#define IFPARSER_H
#include <string>
#include "../../../../Components/Operator/If/If.h"
#include "../../../../Utils/ComponentParserUtils.h"
#include "../../../../FileManager/FileManager.h"

enum class StatusParseIF {
	Active,
	AddSettings,
	NotActive,
	
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
		 default:
			 return "NULL";
			 break;
		 }
	 }
	 size_t checkIfEquals(std::string line);
	 If getEditIfComponent();

	 void ParseIfComponent(std::string line, File& file, int countLine);
 private:
	 std::string stateBetween;
	 StatusParseIF statusParseIF = StatusParseIF::NotActive;

	 If editIfComponent;

};

#endif // !IFPARSER_H
