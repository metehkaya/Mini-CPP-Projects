#include "ConfigData.h"

ConfigData::ConfigData() {
	// TODO Auto-generated constructor stub

}

ConfigData::~ConfigData() {
	// TODO Auto-generated destructor stub
}

bool ConfigData::add(string& field, string& value) {
	bool success;
	map<string,string>::iterator mit = values.find(field);
	if(mit != values.end()) {
		success = false;
		printf("Field %s occurs twice in the config!\n",field.c_str());
	}
	else {
		success = true;
		values.insert(make_pair(field,value));
	}
	return success;
}

string ConfigData::get(string field) {
	string value = "";
	map<string,string>::iterator mit = values.find(field);
	if(mit == values.end())
		printf("Field %s does not exist in the config!\n",field.c_str());
	else
		value = mit->second;
	return value;
}
