#include <string>
#include <iostream>
#include "../../Components/ComponentsManager.h"
enum class ExportStatus {
    OK,
    BAD
};
struct ExportComponent {
    std::string fileName;
    std::string name;
    Component component;
    ExportStatus status;
};

Component getExport(std::string line, std::string fileName) {
    std::size_t exportPos = line.find("export");
    std::size_t startPos = line.find_first_not_of(" \t", exportPos + 6);
    Component exports;
    if (startPos == std::string::npos) {
        return exports;
    }
    std::string afterExport = line.substr(startPos);

    std::size_t startName = afterExport.find("('");
    std::size_t endName = afterExport.find("')");

    if (startName == std::string::npos && endName == std::string::npos) {
        return exports;
    }
        std::string element = afterExport.substr(0, startName);
        std::string name = afterExport.substr(startName + 2, endName - startName - 2);
        exports.setType(getComponentFromString(element));
        exports.setName(name);
        return exports;
}
