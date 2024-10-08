#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include <unordered_map>
#include <stack>

#include "../FileManager/FileManager.h"
#include "../Parser/Import/ParseImport.h"
#include "../Components/Import/Import.h"
#include "../Parser/Export/ParseExport.h"
#include "../Parser/Components/ComponentParser.h"

enum class Token {
	EXPORT,
    COMPONENT,
};

FileManager fileManager;

void parseImport(std::string filename, int countLine, std::string line, File& file) {
    int valid = 0;
    if (line.find("from") != std::string::npos) {
        ImportResultLocal local = getImportLocal(line, countLine, filename, file.getErrorManager());
        if (!local.imports.empty() && local.type != ImportType::Unknown) {
            for (const auto& i : local.imports)
                file.addImport(local.type, i, filename);
        }
        valid = 1;
    }
    if (line.find("<") != std::string::npos && line.find(">") != std::string::npos) {
        ImportResultProject project = getImportFromProject(line, countLine, file.getErrorManager());
        if (project.type != ImportType::Unknown) {
            file.addImport(project.type, project.imports, "Project");
            valid = 1;
        }
    }
    if (valid == 2) {
        file.getErrorManager().addError("Unknow Import: " + line, countLine, ErrorType::ImportNotFound);
    }
}
void parseComponent(File& file, std::stack<Token>& stack, std::string line, int countLine, ParserComponentManager& parserComponent) {
    if (!stack.empty()) {
        if (stack.size() > 0) {
            if (stack.top() == Token::COMPONENT || stack.top() == Token::EXPORT) {
                getParseComponent(line, parserComponent, file, countLine);
            }
        }
    }

    if (line.find("export") != std::string::npos) {
        Component exports = getExport(line);
        if (exports.getName().empty()) return;
            if (!stack.empty()) {
                if (stack.size() > 0) {
                    file.getErrorManager().addError("Syntax error there cannot be another export inside the export: " + RED_COLOR + " " + line, countLine, ErrorType::InsideExport);
                    return;
                }
            }
            stack.push(Token::EXPORT);
            parserComponent.newEditComponent();
            parserComponent.getEditComponent().setType(exports.getType());
            parserComponent.getEditComponent().setName(exports.getName());
    }
}


void parseFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::stack<Token> component;
    File files;
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    int countLine = 0;
    files.setFilePath(filename);
    ParserComponentManager parserComponent;
    while (std::getline(file, line)) {
        if (line.find_first_not_of(" \t") == std::string::npos) continue;
        size_t importPos = line.find("#import");
        if (importPos != std::string::npos) {
            std::string beforeImport = line.substr(0, importPos);
            if (!beforeImport.empty() && beforeImport.find_first_not_of(" \t") != std::string::npos) {
                files.getErrorManager().addError("Syntax error: " + RED_COLOR + beforeImport  + RESET_COLOR + line.substr(importPos), countLine, ErrorType::Syntax);
            } else {
                parseImport(filename, countLine, line, files);
            }
        }
        parseComponent(files, component, line, countLine, parserComponent);
        countLine++;
    }
    file.close();
    fileManager.addFile(files);
}