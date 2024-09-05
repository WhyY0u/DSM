#ifndef COMPONENTPARSER_H
#define COMPONENTPARSER_H

#include <string>
#include <iostream>
#include "Operators/IfParser/IfParser.h"
#include "../../Components/Operator/If/If.h"
#include "../../FileManager/FileManager.h"
#include "../../Utils/ComponentParserUtils.h"

class ParserComponentManager {
public:
	Component getEditComponent();
	void setEditComponent(Component edit);
	void newEditComponent();
	IfParser& getIfParser();
private:
	Component editComponent;
	IfParser ifParser;

};
ParserComponentManager getParseComponent(std::string line, ParserComponentManager& parserManager, File& file, int countLine);

#endif // !COMPONENTPARSER_H
