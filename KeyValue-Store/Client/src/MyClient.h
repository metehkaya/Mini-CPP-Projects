#ifndef MYCLIENT_H_
#define MYCLIENT_H_

#include "ConfigData.h"
#include <windows.h>
#include <winsock.h>
#include <cstdio>
#include <signal.h>
#include <stdio.h>
using namespace std;

//DECLARATIONS
//error trapping signals
#define SIGINT 2
#define SIGKILL 9
#define SIGQUIT 3

class MyClient {
public:
	MyClient(ConfigData* configData);
	virtual ~MyClient();
	void dealClient();
private:
	void s_cl(char *a, int x);
	ConfigData* configData;
};

#endif /* MYCLIENT_H_ */
