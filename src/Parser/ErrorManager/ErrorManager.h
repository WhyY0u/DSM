#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <string>
#include <map>
#include <vector>

enum class ErrorType {
    Syntax,
    ImportNotFound,
};

struct Error {
    std::string text;
    int line;
};

extern std::map<ErrorType, std::vector<Error>> errorMap;

void addError(std::string text, int line, const ErrorType error);

const std::vector<Error>* getErrors(ErrorType type);

#endif 
