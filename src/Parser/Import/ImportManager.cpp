#include "ImportManager.h"

Import getImportFromString(const std::string& str) {
    if (str == "Square") return Import::Square;
    return Import::Unknown;
}
