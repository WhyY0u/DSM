#include "ErrorManager.h"

std::map<ErrorType, std::vector<Error>> errorMap;

void addError(const std::string text, const int line, const ErrorType error) {
    Error errors;
    errors.line = line;
    errors.text = text;
    errorMap[error].push_back(errors);
}

const std::vector<Error>* getErrors(ErrorType type) {
    auto it = errorMap.find(type);
    if (it != errorMap.end()) {
        return &it->second;
    }
    return nullptr;
}
