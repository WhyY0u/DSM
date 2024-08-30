#include "Parser/Parser.h"


int main() {
    parseFile("D:/Dissimilate/DSM/DSM/test/background.dkit");
    for (auto& file : fileManager.getFile()) {
        for (auto& errorT : getAllTypeError()) {
            const std::vector<Error>* errorsPtr = file.getErrorManager().getErrors(errorT);
            std::cout << "oK" << std::endl;
            if (errorsPtr) {
                for (const auto& error : *errorsPtr) {
                    std::cout << error.text << std::endl;
                }
            }
        }
    }
    return 0;
}