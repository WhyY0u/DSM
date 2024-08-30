#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <map>

#include "../Parser/Import/ParseImport.h"
#include "../Parser/ErrorManager/ErrorManager.h"
#include "../Parser/Export/ParseExport.h"
#include "../Parser/Components/ComponentParser.h"
#include "../Components/ComponentsManager.h"

class File {
public:
    void addImport(ImportType type, std::string str, std::string fileName) {
        StructImport sti;
        sti.fileName = fileName;
        sti.imports.push_back(str);
        imports[type].push_back(sti);
    }
    void addComponent(Component component) {
        components.push_back(component);
    }
    void addExport(Component exportComponent) {
        exportList.push_back(exportComponent);
    }
    std::map<ImportType, std::vector<StructImport>> getImports() {
        return imports;
    }
   std::vector<Component> getComponents() {
        return components;
    }
    std::string getPathFile() {
        return pathFile;
    }

    void setFilePath(std::string path) {
        pathFile = path;
    }

    ComponentManager getComponentManager() {
        return componentManager;
    }
    ErrorManager& getErrorManager() {
        return errorManager;
    }
private:
  std::string pathFile;
  std::map<ImportType, std::vector<StructImport>> imports;
  std::vector<Component> components;
  ErrorManager errorManager;
  std::vector<Component> exportList;
  ComponentManager componentManager;
};

class FileManager {

public:
    std::vector<File> getFile() {
        return fileList;
    }
    void addFile(File file) {
        fileList.push_back(file);
    }
private:
	std::vector<File> fileList;
};