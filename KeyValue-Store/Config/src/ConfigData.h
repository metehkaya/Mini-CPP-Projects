#ifndef CONFIGDATA_H_
#define CONFIGDATA_H_

#include <string>
#include <map>
using namespace std;

class ConfigData {
public:
	ConfigData();
	virtual ~ConfigData();
	bool add(string& field, string& value);
	string get(string field);
private:
	map<string,string> values;
};

#endif /* CONFIGDATA_H_ */
