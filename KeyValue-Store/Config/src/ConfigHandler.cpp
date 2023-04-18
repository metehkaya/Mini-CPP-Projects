#include "ConfigHandler.h"

ConfigHandler::ConfigHandler(char* fileName) {
	this->fileName = fileName;
	configData = new ConfigData();
	// this->fileName = malloc(strlen(fileName)+1);
	// strcpy(this->fileName, fileName);
}

ConfigHandler::~ConfigHandler() {
	// TODO Auto-generated destructor stub
}

void ConfigHandler::procLine(const string& line) {
	int idx = line.find("=");
	if(idx != -1) {
		int len = line.length();
		string field = line.substr(0,idx);
		string value = line.substr(idx+1,len-idx-1);
		configData->add(field,value);
	}
	else
		printf("Separator = does not exist in the line : %s\n",line.c_str());
}

void ConfigHandler::readConfig() {
	string line;
	ifstream myfile(fileName);
	if(myfile.is_open()) {
		printf("Reading the config file : %s\n",fileName);
		while(getline(myfile,line))
			procLine(line);
		myfile.close();
	}
	else
		printf("Could not open the config file : %s\n",fileName);
}

ConfigData* ConfigHandler::getConfigData() {
	return configData;
}
