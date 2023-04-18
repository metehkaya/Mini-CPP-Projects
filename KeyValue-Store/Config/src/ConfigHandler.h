#ifndef CONFIGHANDLER_H_
#define CONFIGHANDLER_H_

#include "ConfigData.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

class ConfigHandler {
public:
	ConfigHandler(char* fileName);
	virtual ~ConfigHandler();
	void readConfig();
	ConfigData* getConfigData();
private:
	void procLine(const string& line);
	ConfigData* configData;
	char* fileName;
};

#endif /* CONFIGHANDLER_H_ */
