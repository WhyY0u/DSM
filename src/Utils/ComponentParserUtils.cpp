#include "ComponentParserUtils.h"

static ComponentActiveParse activeParse = ComponentActiveParse::If;

ComponentActiveParse getActiveParse() {
    return activeParse;
}

void setActiveParse(ComponentActiveParse parseType) {
    activeParse = parseType;
}