#ifndef IMPORT_H
#define IMPORT_H
#include <vector>
#include <string>

enum class ImportType {
    Unknown,
    Error,
    Prjoect,
    Local
};
struct StructImport {
    std::vector<std::string> imports;
    std::string fileName;
};

#endif