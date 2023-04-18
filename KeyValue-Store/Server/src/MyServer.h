#ifndef MYSERVER_H_
#define MYSERVER_H_

#include "ConfigData.h"
#include <cstdio>
#include <windows.h>
#include <stdlib.h>
#include <winsock.h>
#include <string>
using namespace std;

typedef struct MyData {
	SOCKET* socket;
	HANDLE* semaphore;
}*PMYDATA;

class MyServer {
public:
	MyServer(ConfigData* configData);
	virtual ~MyServer();
	void dealServer();
	//DWORD WINAPI receive_cmds(LPVOID lpParam);
private:
	ConfigData* configData;
	// int calculate(int from, int to);
	// static DWORD WINAPI receive_cmds(LPVOID lpParam);
};

#endif /* MYSERVER_H_ */
