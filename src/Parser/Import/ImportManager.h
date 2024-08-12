#ifndef IMPORT_MANAGER_H
#define IMPORT_MANAGER_H

#include <string>
#include <vector>

enum class ImportType {
    Unknown,
    Prjoect,
    Local
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