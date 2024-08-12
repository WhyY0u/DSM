#include <string>
#include <iostream>

void getExport(std::string line) {
    std::size_t exportPos = line.find("export");
    std::size_t startPos = line.find_first_not_of(" \t", exportPos + 6);

    if (startPos == std::string::npos) return;

    std::string afterExport = line.substr(startPos);

    std::size_t startName = afterExport.find("('");
    std::size_t endName = afterExport.find("')");

    if (startName == std::string::npos && endName == std::string::npos) return;
        std::string element = afterExport.substr(0, startName);
        std::string name = afterExport.substr(startName + 2, endName - startName - 2);
        std::cout << element << std::endl;
}
