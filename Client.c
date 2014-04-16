#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define RECIEVESIZE 32

int PASSTRY;


int main(int argc, char *argv[]) // 1 = IP (127.0.0.1)   2 = port (6060)
{
	//socket
	in_port_t           serverPort;          // echo server port
	char *              serverIPAddress;
	unsigned int        stringLength;
	int                 bytesRecieved = 0;
	int                 totalBytesRecieved = 0;
	char                *msg;
	char					buffer[RECIEVESIZE];

	serverIPAddress = argv[1];
	serverPort      = atoi(argv[2]);

	printf("\nSERVER IP  :%s",serverIPAddress);
	printf("\nSERVER PORT:%d",serverPort);

	int sockt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockt < 0){
		printf("\nDIE WITH ERROR HERE\n");
		exit(1);
	}
	else
	{
		printf("\ncreated socket");
	}

	/* Construct the server address structure */
	struct sockaddr_in  serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));/* Zero out structure */
	serverAddress.sin_family = AF_INET;/* Internet address family */


	int returnValue = inet_pton(AF_INET, serverIPAddress, &serverAddress.sin_addr.s_addr);

	//check inet
	if(returnValue <0) 
	{
		printf("\ninet failed\n");return 0;
	}
	else
	{
		printf("inet initialized");
	}

	serverAddress.sin_port = htons(serverPort); /* Server port */

	if(connect(sockt,(struct sockaddr * ) &serverAddress,sizeof(serverAddress)) < 0)
	{
		printf("\nfailed to connect\n");
		exit(1);
	}
	else
	{
		printf("\nConnected\n");
		printf("\n------------------Handling Server-----------------------\n"); 
	}


	char stringBuffer[RECIEVESIZE];
	if ((bytesRecieved = recv(sockt, buffer, RECIEVESIZE, 0)) <= 0)
	{
		printf("failed to recv()");
		exit(1);
	}  
	buffer[bytesRecieved-1] = '\0';

	printf("\nRecieved:%s",buffer);
	while(1){
		sendRecieve(sockt);
		stringBuffer[7] = '\0';
	}
}

int sendRecieve(int sockt)
{

	char ID[32];
	char buffer[32];
	printf("\nEnter ID to send:");
	gets(ID);
	ID[sizeof(ID)-1] = '\n';
	send(sockt, ID, sizeof(ID), 0);
	recv(sockt, buffer, RECIEVESIZE, 0);
	printf("\nrecieved:%s",buffer);
	return 1;
}




