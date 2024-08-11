#ifndef IMPORT_MANAGER_H
#define IMPORT_MANAGER_H

#include <string>
#include <vector>

enum class Import {
    Unknown,
    Square,
};

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
Import getImportFromString(const std::string& str);


#endif 