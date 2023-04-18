#include "ConfigHandler.h"
#include "ConfigData.h"
#include "MyServer.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
using namespace std;

int main(int argc, char **argv) {
	SetConsoleTitle("TCP Server");
	if(argc != 2) {
		printf("Non-expected number of arguments\n");
		printf("Number of arguments: %d\n",argc-1);
		printf("Expected number of arguments: 1\n");
	}
	ConfigHandler* configHandler = new ConfigHandler(argv[1]);
	configHandler->readConfig();
	ConfigData* configData = configHandler->getConfigData();
	MyServer* myServer = new MyServer(configData);
	myServer->dealServer();
	return 0;
}
