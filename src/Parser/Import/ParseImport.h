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
#include "ImportManager.h"
#include "../ErrorManager/ErrorManager.h"
#include "../../Utils/FileUtils.h"

bool checkIsImportLocal(const std::string& line) {
	if (line.find("<") != std::string::npos && line.rfind(">") != std::string::npos) return false;
	if (line.find("from") != std::string::npos) return true;
	return false;
}

ImportResultLocal getImportLocal(std::string line, int lineNumber, std::string fileName) {
	size_t startS = line.find('{');
	size_t endS = line.find('}');
	size_t startF = line.find("from");

	size_t startUS = line.find("'");
	size_t endUS = line.rfind("'");

	if (startS == std::string::npos || endS == std::string::npos ||
		startS >= startF || endS >= startF || startF >= startUS ||
		startF >= endUS) {
		addError("Syntax error unknown declaration: " + RED_COLOR, lineNumber, ErrorType::Syntax);
		return ImportResultLocal();
	}

	std::string result = line.substr(startS + 1, endS - startS - 1);

	std::string from = line.substr(startUS + 1, endUS - startUS - 1);
	std::cout << from << std::endl;
	ImportResultLocal local;
	local.type = ImportType::Local;
	local.from = fileName;
	if (result.find(",") != std::string::npos) {
		for (const auto& imports : split(result, ',')) {
			local.imports.push_back(imports);
		}
	} else {
		local.imports.push_back(result);
	}


	return local;
}

ImportResultProject getImportFromProject(std::string line, int lineNumber) {
	size_t start = line.find('<');
	size_t end = line.find('>');
	std::string result = line.substr(start + 1, end - start - 1);
	std::string checkerror = line.substr(end + 1);
	if (checkerror.length() != 0) {
		addError("Syntax error unknown declaration: " + line.substr(0, end + 1) + " " + RED_COLOR + " " + checkerror + " " + RESET_COLOR, lineNumber, ErrorType::Syntax);
		return ImportResultProject();
	}

	if (getImportFromString(result) == Import::Unknown) {
		addError("Error import not found: " + line.substr(0, start) + " " + RED_COLOR + " " + result + " " + RESET_COLOR, lineNumber, ErrorType::ImportNotFound);
		return ImportResultProject();
	}
	ImportResultProject ir;
	ir.imports = result;
	ir.type = ImportType::Prjoect;
	return ir;
}



