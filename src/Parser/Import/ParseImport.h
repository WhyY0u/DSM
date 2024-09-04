#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <iterator>

#include "../../Utils/ErrorUtils.h"
#include "../ErrorManager/ErrorManager.h"
#include "../../Utils/FileUtils.h"
#include "../../Components/ComponentsManager.h"
#include "../../Components/Import/Import.h"


struct ImportResultLocal {
	ImportType type;
	std::vector<std::string> imports;
	std::string from;
};
struct ImportResultProject {
	ImportType type;
	std::string imports;
};


bool checkIsImportLocal(const std::string& line) {
	if (line.find("<") != std::string::npos && line.rfind(">") != std::string::npos) return false;
	if (line.find("from") != std::string::npos) return true;
	return false;
}

void checkErrorImportLocal(std::string line, ErrorManager& error, bool& itsError, int lineNumber, size_t startS, size_t startF, size_t endS, size_t startUS, size_t endUS, size_t importPos) {
	if (startS == std::string::npos || endS == std::string::npos) {
		error.addError("Syntax error parentheses defining the object were not found: " + RED_COLOR + line + RESET_COLOR, lineNumber, ErrorType::Syntax);
		itsError = true;
	}
	if (startS >= startF || endS >= startF) {
		error.addError("Syntax error the closing brackets defining the object must be placed after the pointer from where the object starts: " + RED_COLOR + line + RESET_COLOR, lineNumber, ErrorType::Syntax);
		itsError = true;
	}
	if (startF >= startUS || startF >= endUS) {
		error.addError("Syntax error the from indication should stand as a pointer to the object: " + RED_COLOR + line + RESET_COLOR, lineNumber, ErrorType::Syntax);
		itsError = true;
	}

	std::string check = line.substr(importPos + 7, startS - (importPos + 7));
	if (check.find_first_not_of(" \t") != std::string::npos) {
		error.addError("Syntax error: " + line.substr(0, importPos + 7) + RED_COLOR + check + RESET_COLOR + line.substr(startS), lineNumber, ErrorType::Syntax);
		itsError = true;
	}

	size_t posAfterBrace = endS + 1;
	std::string check2 = line.substr(posAfterBrace, startF - posAfterBrace);

	size_t startCheck2 = check2.find_first_not_of(" \t");
	size_t endCheck2 = check2.find_last_not_of(" \t");

	if (startCheck2 != std::string::npos && endCheck2 != std::string::npos) {
		error.addError("Syntax error: " + line.substr(0, endS + 1) + RED_COLOR + check2 + RESET_COLOR + line.substr(startF), lineNumber, ErrorType::Syntax);
		itsError = true;
	}

	size_t posFrom = startF + 4;
	std::string check3 = line.substr(posFrom, startUS - posFrom);
	size_t startCheck3 = check3.find_first_not_of(" \t");
	size_t endCheck3 = check3.find_last_not_of(" \t");

	if (startCheck3 != std::string::npos && endCheck3 != std::string::npos) {
		error.addError("Syntax error: " + line.substr(0, startF + 4) + RED_COLOR + check3 + RESET_COLOR + line.substr(startUS), lineNumber, ErrorType::Syntax);
		itsError = true;
	}
	size_t posUS = endUS + 1;
	std::string check4 = line.substr(posUS);

	size_t startCheck4 = check4.find_first_not_of(" \t");
	size_t endCheck4 = check4.find_last_not_of(" \t");

	if (startCheck4 != std::string::npos && endCheck4 != std::string::npos) {
		error.addError("Syntax error: " + line.substr(0, endUS + 1) + RED_COLOR + check4 + RESET_COLOR, lineNumber, ErrorType::Syntax);
		itsError = true;
	}

}

ImportResultLocal getImportLocal(std::string line, int lineNumber, std::string fileName, ErrorManager& error) {
	size_t startS = line.find('{');
	size_t endS = line.find('}');
	size_t startF = line.find("from");

	size_t startUS = line.find("'");
	size_t endUS = line.rfind("'");
	size_t importPos = line.find("#import");

	bool itsError = false;
	checkErrorImportLocal(line, error, itsError, lineNumber, startS, startF, endS, startUS, endUS, importPos);
	if (!itsError) {
		std::string result = line.substr(startS + 1, endS - startS - 1);
		ImportResultLocal local;
		local.type = ImportType::Local;
		local.from = fileName;
		if (result.find(",") != std::string::npos) {
			for (const auto& imports : split(result, ',')) {
				local.imports.push_back(imports);
			}
		}
		else {
			local.imports.push_back(result);
		}
		return local;
	}
	else {
		ImportResultLocal error;
		error.type = ImportType::Error;
		return error;
    }
	
}

ImportResultProject getImportFromProject(std::string line, int lineNumber, ErrorManager& error) {
	size_t start = line.find('<');
	size_t end = line.find('>');
	std::string result = line.substr(start + 1, end - start - 1);
	std::string checkerror = line.substr(end + 1);
	if (checkerror.length() != 0) {
		error.addError("Syntax error unknown declaration: " + line.substr(0, end + 1) + " " + RED_COLOR + " " + checkerror + " " + RESET_COLOR, lineNumber, ErrorType::Syntax);
		ImportResultProject er;
		er.type = ImportType::Error;
		return er;
	}

	size_t importPos = line.find("#import");
	std::string check1 = line.substr(importPos + 7, start - (importPos + 7));

	if (check1.find_first_not_of(" \t") != std::string::npos) {
		error.addError("Syntax error unknown declaration: " + line.substr(0, importPos + 7) + " " + RED_COLOR + " " + check1 + " " + RESET_COLOR, lineNumber, ErrorType::Syntax);
		ImportResultProject er;
		er.type = ImportType::Error;
		return er;
	}


	if (getComponentFromString(result) == ComponentType::Unknown) {
		error.addError("Error import not found: " + line.substr(0, start) + " " + RED_COLOR + " " + result + " " + RESET_COLOR, lineNumber, ErrorType::ImportNotFound);
		ImportResultProject er;
		er.type = ImportType::Error;
		return er;
	}

	ImportResultProject ir;
	ir.imports = result;
	ir.type = ImportType::Prjoect;
	return ir;
}



