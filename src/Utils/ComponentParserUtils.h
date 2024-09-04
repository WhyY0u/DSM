#ifndef COMPONENTPARSERUTILS_H
#define COMPONENTPARSERUTILS_H
enum class ComponentActiveParse {
	If,
	Setting,
	IfSettings,
	InsideIF,
	None,
};
ComponentActiveParse getActiveParse();
void setActiveParse(ComponentActiveParse parseType);
#endif
