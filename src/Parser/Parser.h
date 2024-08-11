#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include <unordered_map>
#include <stack>

#include "Import/ParseImport.h"
#include "ErrorManager/ErrorManager.h"
#include "Export/ParseExport.h"

enum class Type {
	IMPORT,
	EXPORT,
};

struct StructImport {
    std::vector<std::string> imports;
    std::string fileName;
};

class ParserManager {
public:
    void addImport(ImportType type, std::string str, std::string fileName) {
        StructImport sti;
        sti.fileName = fileName;
        sti.imports.push_back(str);
        imports[type].push_back(sti);
    }
    void addError(int line, std::string error) {
        errorList[line] = error;
    }
    std::map<ImportType, std::vector<StructImport>> getImports() {
        return imports;
    }
    std::unordered_map<int, std::string> getErrorList() {
        return errorList;
    }
private:
    std::map<ImportType, std::vector<StructImport>> imports;
    std::unordered_map<int, std::string> errorList;
};

ParserManager manager;

void parseImport(std::string filename, int countLine, std::string line) {
    if (line.find("from") != std::string::npos) {
        ImportResultLocal local = getImportLocal(line, countLine, filename);
        if (!local.imports.empty() && local.type != ImportType::Unknown) {
            for (const auto& i : local.imports)
                manager.addImport(local.type, i, filename);
        }
    }
    if (line.find("<") != std::string::npos && line.find(">") != std::string::npos) {
        ImportResultProject project = getImportFromProject(line, countLine);
        manager.addImport(project.type, project.imports, "Project");
    }
}

void parseExport(std::string line) {
    getExport(line);
}

void parseFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::stack<int> bracket;
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    int countLine = 0;
    while (std::getline(file, line)) {
        if (line.find("#import") == 0) {
            parseImport(filename, countLine, line);
        }
        if (line.find("{") != std::string::npos) {
            if (line.find("export") == 0) {
                parseExport(line);
            }
            bracket.push(countLine);
        }
        if (line.find("}") != std::string::npos) {
            std::cout << " line: " << line << std::endl;
            bracket.pop();
        }
        countLine++;
    }

    file.close();
    if (errorMap.size() != 0) {
        for (const auto& t : errorMap) {
            ErrorType type = t.first;
            for (const auto& v : t.second) {
                std::cout << v.text << std::endl;
            }
        }
    } else {
       
    }
}