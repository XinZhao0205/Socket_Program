#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>
#include<arpa/inet.h>
#define EDGE_UDP_PORT                       24508
#define EDGE_TCP_PORT                       23508
#define AND_UDP_PORT                        22508
#define OR_UDP_PORT                         21508 

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	printf("The edge server is up and run.\n");
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(EDGE_TCP_PORT);

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		error("ERROR on binding");
	}

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0)
	{
		error("ERROR on accept");
	}

	bzero(buffer,256);

	n = read(newsockfd,buffer,255);

	if (n < 0)
	{
		error("ERROR reading from socket");
	}


	//judge
	
	char and_arr[1024],or_arr[1024];
	int i=0,and_lines=0,or_lines=0;
	*and_arr='\0',*or_arr='\0';
	char *p=strtok(buffer,"\n");
	char First[10];
	*First='\0';
	strncat(First,p,1);
	
	if (strcmp(First,"a")==0){
		strcat(and_arr,p);
		strcat(and_arr,"\n");
		and_lines++;
		
	}
	else{
		strcat(or_arr,p);
		strcat(or_arr,"\n");
		or_lines++;}		

	while(p!=NULL){
		
		p = strtok(NULL,"\n");
		i++;
		if (p==NULL){break;}
		*First='\0';
		strncat(First,p,1);		
		if (strcmp(First,"a")==0){
			strcat(and_arr,p);
			strcat(and_arr,"\n");
			and_lines++;}
			
		else{
			strcat(or_arr,p);
			strcat(or_arr,"\n");
			or_lines++;}

	}

	printf("The edge server has received %d lines from the client using TCP over port %d.\n",i,EDGE_TCP_PORT);
	
	//AND UDP
	int sock=socket(AF_INET,SOCK_DGRAM,0),n1 ;
	char and_output[256];
	struct sockaddr_in remote;
	struct hostent *hp;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(AND_UDP_PORT);
	remote.sin_addr.s_addr=INADDR_ANY;

	int len=sizeof(remote);
	if (sock<0)
	{
		error("socket");
	}

	
	printf("The edge server has successfully sent %d lines to Backend-Server AND.\n",and_lines);
	n1=sendto(sock,and_arr,strlen(and_arr),0,(struct sockaddr*)&remote,len);
	if(n1<0){
		perror("sendto");
	}
	n1=recvfrom(sock,and_output,sizeof(and_output)-1,0,(struct sockaddr*)&remote,&len);
	if(n1<0){
		perror("recvfrom\n");
	}

	
	//OR UDP
	int sock1=socket(AF_INET,SOCK_DGRAM,0),n2 ;
	char or_output[256];
	struct sockaddr_in or_server;
	struct hostent *hp1;
	or_server.sin_family=AF_INET;
	or_server.sin_port=htons(OR_UDP_PORT);
	or_server.sin_addr.s_addr=INADDR_ANY;

	int len1=sizeof(or_server);
	if (sock1<0)
	{
		error("socket");
	}

	
	printf("The edge server has successfully sent %d lines to Backend-Server OR.\n",or_lines);
	n2=sendto(sock1,or_arr,strlen(or_arr),0,(struct sockaddr*)&or_server,len1);
	if(n2<0){
		perror("sendto");
	}
	
	n2=recvfrom(sock1,or_output,sizeof(or_output)-1,0,(struct sockaddr*)&or_server,&len1);
	if(n2<0){
		perror("recvfrom\n");
	}
	printf("The edge server start receiving the computation results from Backend-Server OR and  Backend-Server And using UDP port %d.\n",EDGE_UDP_PORT);
	printf("The computation results are: \n%s\n%s\n",or_output,and_output);
	printf("The edge server has successfully finished receiving all computation results from the Backend-Server OR and Backend-Server AND.\n");
	
	char buffer1[256];
	strcat(buffer1,or_output);
	strcat(buffer1,and_output);
	n = write(newsockfd,buffer1,255);
	if (n < 0)
	{
		error("ERROR writing to socket");
	}
	else{
		printf("The edge server has successfully finished sending all computation results to the clients.\n");}
	return 0;
}

