#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#define EDGE_UDP_PORT                       24508
#define EDGE_TCP_PORT                       23508
#define AND_UDP_PORT                        22508
#define OR_UDP_PORT                         21508 

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	
	printf("The client is up and run.\n");   	
	//read file
	char arr[20][100] = {'\0'};
	int ret = 0, index =0,i=0;
	FILE *stream;

	stream = fopen( "test.txt", "r" );

	do
	{
	ret = fscanf(stream,"%s",arr[index++]);
	
	}while(ret != 0 && ret != EOF);

	//output

	char buffer[1024]="\0";
	index=index-2;
	while(index >= 0)
	{
	strcat(buffer,arr[index--]);
	strcat(buffer,"\n");
	i++;
	}

	int sockfd,n;
	

	char buffer2[1024]="\0";
	strcpy(buffer2,buffer);
	
	struct sockaddr_in serv_addr;
	struct hostent *server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname("ee450");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
	serv_addr.sin_port = htons(EDGE_TCP_PORT);
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	printf("The client has successfully sent %d lines to edge server.\n",i);
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0) 
		error("ERROR writing to socket");
	bzero(buffer,1024);
	

	
	

	



	char correct[1024];
	*correct='\0';
	char *buf=buffer2;
	char *token = strsep(&buf,"\n");
	char c[] = ",";
	char *p = strtok(token,",");
	char *input1=p;
	p = strtok(NULL,c);
	char *input2=p;
	p = strtok(NULL,c); 
	char *input3=p;
	

	
	
	if(*input1==97){
		

		if(strlen(input2)<strlen(input3)){
		char *k=input3;
		char *t=input2;
		input3=t;
		input2=k;}


		strcat(correct,input2);
		strcat(correct," ");
		strcat(correct,input1);
		strcat(correct," ");
		strcat(correct,input3);
		strcat(correct," ");
		strcat(correct,"\n");
		}

	else{	
		if(strlen(input3)<strlen(input2)){
			char *k=input2;
			char *t=input3;
			input2=t;
			input3=k;}


		strcat(correct,input2);
		strcat(correct," ");
		strcat(correct,input1);
		strcat(correct," ");
		strcat(correct,input3);
		strcat(correct," ");
		strcat(correct,"\n");
		}

	while(token!=NULL){
		token = strsep(&buf,"\n");
		char *p = strtok(token,c);
		
		if(p==NULL){break;}
		char *input1=p;
		p = strtok(NULL,c);
		char *input2=p;
		p = strtok(NULL,c); 
		char *input3=p;

	

	if(*input1==97){
		

		if(strlen(input2)<strlen(input3)){
			char *k=input3;
			char *t=input2;
			input3=t;
			input2=k;}


		strcat(correct,input2);
		strcat(correct," ");
		strcat(correct,input1);
		strcat(correct," ");
		strcat(correct,input3);
		strcat(correct," ");
		strcat(correct,"\n");}

	else{	
		if(strlen(input3)<strlen(input2)){
		char *k=input2;
		char *t=input3;
		input2=t;
		input3=k;}


		strcat(correct,input2);
		strcat(correct," ");
		strcat(correct,input1);
		strcat(correct," ");
		strcat(correct,input3);
		strcat(correct," ");
		strcat(correct,"\n");}

	}
	






char buffer1[1024]="\0";
	n = read(sockfd,buffer1,1024);
	if (n < 0) 
		error("ERROR reading from socket");
		




	char answer[1024];
	*answer='\0';

	char correct_line[1024];
	*correct_line='\0';
	strcpy(correct_line,correct);

	char *buf1=buffer1;

	char *token1 = strsep(&buf1,"\n");
	char *p1 = strtok(token1,"=");
	char *qua=p1;
	p1 = strtok(NULL,"\n");
	char *res=p1;
	
	
	
	char *cor=correct;
	char *corline = strsep(&cor,"\n");
	
	if(strcmp(qua,corline)==0){strcat(answer,res);
			strcat(answer,"\n");}
	
	while(corline!=NULL){		
		corline = strsep(&cor,"\n");
		
		if(corline==NULL){break;}
		if(strcmp(qua,corline)==0){
						
			strcat(answer,res);
			strcat(answer,"\n");}
		}



	
	
	while(token1!=NULL){
		token1 = strsep(&buf1,"\n");
		char *p1 = strtok(token1,"=");
		if(p1==NULL){break;}	
		char *qua1=p1;
		p1 = strtok(NULL,c);
		char *res1=p1;
		
		char str[1024];
		*str='\0';
		strcpy(str,correct_line);
		char *cor1=str;
		
		char *corline1 = strsep(&cor1,"\n");

		if(strcmp(qua1,corline1)==0){				
				strcat(answer,res1);
				strcat(answer,"\n");		
		}

		while(corline1!=NULL){	

			corline1 = strsep(&cor1,"\n");
			if(cor1==NULL){break;}
			if(strcmp(qua1,corline1)==0){
						
				strcat(answer,res1);
				strcat(answer,"\n");}
		}
	}







	printf("The final computation results are:\n%s\n",answer);
	printf("The client has successfully finished receiving all computation results from the edge server.\n");
	return 0;
}
