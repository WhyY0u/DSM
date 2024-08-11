#include "FileUtils.h"


bool hasExtension(const std::string& filePath, const std::string& extension) {
    if (filePath.length() < extension.length()) {
        return false;
    }
    return filePath.compare(filePath.length() - extension.length(), extension.length(), extension) == 0;
}

std::string readFileDkit(const std::string& filePath) {
    if (!hasExtension(filePath, ".dkit")) {
        throw std::runtime_error("File is not of type .dkit");
    }
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> customImports;
    std::istringstream stream(str);
    std::string im;
    while (std::getline(stream, im, ',')) {
        customImports.push_back(im);
    }
    return customImports;
}
