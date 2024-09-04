#ifndef IFPARSER_H
#define IFPARSER_H
#include <string>
#include "../../../../Components/Operator/If/If.h"
#include "../../../../Utils/ComponentParserUtils.h"
enum class StatusParseIF {
	Active,
	AddSettings,
	NotActive,
	
};
class IfParser {

 public:
	 IfParser(){}
	 void ParseIfComponent(std::string line);
 private:
	 If getEditIfComponent();
	 std::string getStateBetween();
	 void setStateBetween(std::string string);
	 std::string stateBetween;
	 StatusParseIF statusParseIF = StatusParseIF::NotActive;
	 StatusParseIF getStatusParseIF();

	 If editIfComponent;
	 size_t checkIfEquals(std::string line);
	 void setStatusParseIF(StatusParseIF state);
	 void setIfEditComponent(If ifs);

};

#endif // !IFPARSER_H
