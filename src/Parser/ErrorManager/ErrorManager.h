#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <string>
#include <map>
#include <vector>

enum class ErrorType {
    Syntax,
    ImportNotFound,
    InsideExport
};

struct Error {
    std::string text;
    int line;
};
std::vector<ErrorType> getAllTypeError();
class ErrorManager {

public:
    void addError(std::string text, int line, const ErrorType error);
    const std::vector<Error>* getErrors(ErrorType type);
private:
    std::map<ErrorType, std::vector<Error>> errorMap;
};





#endif 
