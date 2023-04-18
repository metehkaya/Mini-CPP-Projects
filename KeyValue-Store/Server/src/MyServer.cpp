#include "MyServer.h"
#include "KeyValueStore.h"
#include <thread>

MyServer::MyServer(ConfigData* configData) {
	// TODO Auto-generated constructor stub
	this->configData = configData;
}

MyServer::~MyServer() {
	// TODO Auto-generated destructor stub
}

HANDLE semaphore;
KeyValueStore* keyValueStore;

// our thread for recving commands
DWORD WINAPI receive_cmds(LPVOID lpParam)
{
	// printf("thread created\r\n");

	// set our socket to the socket passed in as a parameter
	SOCKET current_client = (SOCKET)lpParam;

	// buffer to hold our recived data
	char buf[1000];
	// buffer to hold our sent data
	char sendData[1000];
	// for error checking
	int res;

	// our recv loop
	while(true) {
		res = recv(current_client,buf,sizeof(buf),0); // recv cmds
		Sleep(10);
		// printf("res : %d , buf : %s\n",res,buf);
		if(res == 0) {
			MessageBox(0,"error","error",MB_OK);
			closesocket(current_client);
			ExitThread(0);
		}
		else if(res == -1) {
			printf("Client connection is lost\n");
			closesocket(current_client);
			ExitThread(0);
		}
		WaitForSingleObject(semaphore, INFINITE);
		string s = buf;
		string response = keyValueStore->procCmd(s);
		ReleaseSemaphore(semaphore,1,0);
		strcpy(sendData,response.c_str());
		Sleep(10);
		send(current_client,sendData,sizeof(sendData),0);
		// clear buffers
		strcpy(sendData,"");
		strcpy(buf,"");
	}
}

void MyServer::dealServer() {

	puts("Starting TCP Server\n");

	// our masterSocket(socket that listens for connections)
	SOCKET sock;

	// for our thread
	DWORD my_thread;

	WSADATA wsaData;
	sockaddr_in server;

	// start winsock
	int ret = WSAStartup(0x101,&wsaData); // use highest version of winsock avalible

	if(ret != 0)
		return;

	semaphore = CreateSemaphore(NULL,1,1,NULL);
	if(semaphore == NULL) {
		printf("Semaphore could not be created!\n");
		return;
	}

	// fill in winsock struct ...
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	string port_str = configData->get("PORT");
	int port_num = stoi(port_str);
	server.sin_port=htons(port_num); // listen on telnet port 23

	// create our socket
	sock=socket(AF_INET,SOCK_STREAM,0);

	if(sock == INVALID_SOCKET)
		return;

	// bind our socket to a port
	if( bind(sock,(sockaddr*)&server,sizeof(server)) !=0 )
		return;

	// listen for a connection
	if(listen(sock,5) != 0)
		return;

	// socket that we snedzrecv data on
	SOCKET client;

	sockaddr_in from;
	int fromlen = sizeof(from);

	string storeMemory_str = configData->get("MEMORY");
	int storeMemory = stoi(storeMemory_str);
	string diskMemoryPath = configData->get("PATH");

	keyValueStore = new KeyValueStore(storeMemory,diskMemoryPath);

	// loop forever
	while(true)
	{
		// accept connections
		client = accept(sock,(struct sockaddr*)&from,&fromlen);
		puts("Client connected");
		// create our recv_cmds thread and parse client socket as a parameter
		// PMYDATA args;
		// args->socket = client;
		// args->semaphore = semaphore;
		CreateThread(NULL, 0,receive_cmds,(LPVOID)client, 0, &my_thread);
		// thread t1(&MyServer::calculate, this,  0, 10);
	}

	// shutdown winsock
	closesocket(sock);
	WSACleanup();
}
