#include "MyClient.h"

// SOCKETS
SOCKET sock,client;

MyClient::MyClient(ConfigData* configData) {
	// TODO Auto-generated constructor stub
	this->configData = configData;
}

MyClient::~MyClient() {
	// TODO Auto-generated destructor stub
}

void s_handle(int s) {
    if(sock)
       closesocket(sock);
    if(client)
       closesocket(client);
    WSACleanup();
    Sleep(1000);
    printf("EXIT SIGNAL : %d\n",s);
    exit(0);
}


void MyClient::s_cl(char *a, int x) {
    printf("%s\n",a);
    s_handle(x+1000);
}

void MyClient::dealClient() {

    char ip[15];
    WSADATA data;

    signal(SIGINT,s_handle);
    signal(SIGKILL,s_handle);
    signal(SIGQUIT,s_handle);

    string ip_str = configData->get("IP");
    strcpy(ip, ip_str.c_str());

    sockaddr_in ser;
    sockaddr addr;

	string port_str = configData->get("PORT");
	int port_num = stoi(port_str);

    ser.sin_family=AF_INET;
    ser.sin_port=htons(port_num);                    //Set the port
    ser.sin_addr.s_addr=inet_addr(ip);      //Set the address we want to connect to

    memcpy(&addr,&ser,sizeof(SOCKADDR_IN));

    int res = WSAStartup(MAKEWORD(1,1),&data);      //Start Winsock

    if(res != 0)
        s_cl("WSAStarup failed",WSAGetLastError());

    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);       //Create the socket
        if(sock==INVALID_SOCKET )
            s_cl("Invalid Socket ",WSAGetLastError());
        else if(sock==SOCKET_ERROR)
            s_cl("Socket Error)",WSAGetLastError());
        else
            printf("Socket Established\n");

    res=connect(sock,&addr,sizeof(addr));               //Connect to the server
	if(res !=0 )
	{
		s_cl("SERVER UNAVAILABLE",res);
	}
	else
	{
		puts("Connected to Server");
		memcpy(&ser,&addr,sizeof(SOCKADDR));
	}

	char buf[1000];
    char RecvdData[1000] = "";
    int ret;

    while(true)
    {
        strcpy(buf,"");
        printf("Enter message to send : ");
        fgets(buf,sizeof(buf),stdin);

        Sleep(5);
        res = send(sock,buf,sizeof(buf),0);
        // printf("res = %d\n",res);

         if(res==0)
         {
            //0==other side terminated conn
            printf("\nSERVER terminated connection\n");
            Sleep(40);
            closesocket(client);
            client = 0;
            break;
         }
         else if(res==SOCKET_ERROR)
         {
            //-1 == send error
            printf("Socket error\n");
            Sleep(40);
            s_handle(res);
            break;
         }

       ret = recv(sock,RecvdData,sizeof(RecvdData),0);
       // printf("ret = %d\n",ret);
       if(ret > 0)
       {
        printf("%s\n",RecvdData);
        strcpy(RecvdData,"");
       }
    }

    closesocket(client);
    WSACleanup();
}
