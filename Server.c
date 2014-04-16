#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32
#define SENDBUFFSIZE 32

int PASSTRY;
// used in my second draft of the project 
int sendcount;
int recievecount;
int USERNUM;

void DieWithError(char *errorMessage);
void HandleTCPClient(int clntSocket);

int main(int argc, char *argv[]) // input port
{
	int 		serverSock;
	in_port_t	serverPort;
	char           echoBuffer[RCVBUFSIZE];
	char           stringBuffer[] = "Welcome to the Server\n";
	char echoClientName[INET_ADDRSTRLEN]; // String to contain client address
	int clientSock = 0;
	struct sockaddr_in echoClientAddress;
	serverPort = atoi(argv[1]);  //char to int
	struct sockaddr_in echoServerAddress;

	if((serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		printf("\nEXIT WITH ERROR\n");
		exit(1);
	}
	else
	{
		printf("socket created\n");
	}
	//local address
	memset(&echoServerAddress, 0, sizeof(echoServerAddress));//zero out
	echoServerAddress.sin_family = AF_INET;//internet address family
	echoServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServerAddress.sin_port = htons(serverPort);
	//**************************bind******************************
	if(bind(serverSock, (struct sockaddr *) &echoServerAddress, sizeof(echoServerAddress))< 0)
	{
		printf("\nfailed to bind\n");exit(1);}else{printf("\nbind initiated\n");
		}
		/* Mark the socket so it will listen for incoming connections */
		//**************************listen******************************
		while(1)
		{
			if (listen(serverSock, MAXPENDING) < 0)
			{
				printf("\n failed to listen()\n");exit(1);
			}
			else
			{
				printf("\nListening\n");
			}

			socklen_t clientLength = sizeof(echoClientAddress);
			//**************************accept******************************
			clientSock = accept(serverSock, (struct sockaddr*) &echoClientAddress, &clientLength);

			if (inet_ntop(AF_INET, &echoClientAddress.sin_addr.s_addr, echoClientName,sizeof(echoClientName)) != NULL)
			{
				printf("Handling client %s/%d\n", echoClientName, ntohs(echoClientAddress.sin_port));
			}
			else
			{
				puts("Unable to get client address");
			}

			printf("\n------------------Handling Client-----------------------\n"); 
			send(clientSock, stringBuffer, strlen(stringBuffer), 0);
			while(1){
				sendRecieve(clientSock);
			}


		}
}

int sendRecieve(int sockt)
{
	char buffer[32];
	char buffer2[] = "fluff\0";
	int pairs = 5;
	int i = 0;
	char ID[32];
	int bytesRecieved;
	bytesRecieved = recv(sockt, buffer, RCVBUFSIZE, 0);
	printf("ID reciever:%s\n",buffer);
	send(sockt, buffer, sizeof(buffer), 0);
	return 1;

}

