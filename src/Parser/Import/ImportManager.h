#ifndef IMPORT_MANAGER_H
#define IMPORT_MANAGER_H

#include <string>
#include <vector>

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
struct ImportResultLocal {
    ImportType type;
    std::vector<std::string> imports;
    std::string from;
};
struct ImportResultProject {
    ImportType type;
    std::string imports;
};


#endif 