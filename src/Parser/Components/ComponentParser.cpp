#include "ComponentParser.h"



ParserComponentManager getParseComponent(std::string line, ParserComponentManager& parserManager, File& file, int countLine) {
	std::cout << "LINE PARSE: " << line << std::endl;
	if (line.length() == 0 || line.find_first_not_of(" \t") == std::string::npos) return parserManager;
	size_t ifs = line.find("if");
	if (ifs != std::string::npos || (getActiveParse() == ComponentActiveParse::If || getActiveParse() == ComponentActiveParse::IfSettings || getActiveParse() == ComponentActiveParse::InsideIF)) {
		IfParser& parser = parserManager.getIfParser();
		parser.ParseIfComponent(line, file, countLine);
	}
	
	
	return parserManager;
} 

void setParseComponent(Component component, ParserComponentManager componentManager) {
	Component edit = componentManager.getEditComponent();
	if (edit.getName().empty()) {
		componentManager.setEditComponent(component);
	}
}


Component ParserComponentManager::getEditComponent() {
	return ParserComponentManager::editComponent;
}


void ParserComponentManager::setEditComponent(Component edit) {
	ParserComponentManager::editComponent = edit;
}

void ParserComponentManager::newEditComponent() {
	ParserComponentManager::editComponent = Component();
}



IfParser& ParserComponentManager::getIfParser()
{
	 return ifParser; 
}


