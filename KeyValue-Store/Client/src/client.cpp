#include "ConfigHandler.h"
#include "ConfigData.h"
#include "MyClient.h"
using namespace std;

int main(int argc, char **argv) {
	SetConsoleTitle("TCP Client");
	if(argc != 2) {
		printf("Non-expected number of arguments\n");
		printf("Number of arguments: %d\n",argc-1);
		printf("Expected number of arguments: 1\n");
	}
	ConfigHandler* configHandler = new ConfigHandler(argv[1]);
	configHandler->readConfig();
	ConfigData* configData = configHandler->getConfigData();
	// MyClasss* myClasss = new MyClasss();
	MyClient* myClient = new MyClient(configData);
	myClient->dealClient();
	return 0;
}
