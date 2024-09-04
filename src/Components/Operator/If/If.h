#ifndef IF_H
#define IF_H
#include <iostream>
#include <vector>
#include "../../Settings/Settings.h"

class If {
private:
	bool active;
	std::vector<Setting> getSettings();
	void addSettings(Setting settings);
public:
	bool getActive();
	bool setActive();
	std::vector<Setting> settings;
};

#endif // !IF_H


