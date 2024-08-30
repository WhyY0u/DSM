#include "ErrorManager.h"


void ErrorManager::addError(const std::string text, const int line, const ErrorType error) {
    errorMap[error].emplace_back(Error{text, line });
}

const std::vector<Error>* ErrorManager::getErrors(ErrorType type)  {
    auto it = errorMap.find(type);
    if (it != errorMap.end()) {
        return &it->second;
    }
    return nullptr;
}


std::vector<ErrorType> getAllTypeError() {
    return {ErrorType::ImportNotFound, ErrorType::InsideExport, ErrorType::Syntax};
}
