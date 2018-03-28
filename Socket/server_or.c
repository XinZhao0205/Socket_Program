#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#define EDGE_UDP_PORT                       24508
#define EDGE_TCP_PORT                       23508
#define AND_UDP_PORT                        22508
#define OR_UDP_PORT                         21508 
int main() 
{
	printf("The Server OR is up and running using UDP on port %d\n.",OR_UDP_PORT);	
	int sock=socket(AF_INET,SOCK_DGRAM,0),n;
	if(sock<0)
	{
		perror("socket");
	}

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(OR_UDP_PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(sock,(struct sockaddr*)&server,sizeof(server));

	struct sockaddr_in remote;
	char buffer[1024];
        int len=sizeof(remote);
	

	while(1)
	{
		memset(buffer,'\0',sizeof(buffer));
		n=recvfrom(sock,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&remote,&len);
	
		if(n <0){
			perror("recvfrom\n"); 
		}
		
		printf("The Server OR start reveiving lines from the edge server for OR computation.\n");
		
		
	
		//The process of or operation.
		char output[1024];
		*output='\0';
		char *buf=buffer;
		char *token = strsep(&buf,"\n");
		int i=0;
		char c[] = ",";
		char *p = strtok(token,c);
		char *input1=p;
		p = strtok(NULL,c);
		char *input2=p;
		p = strtok(NULL,c); 
		char *input3=p;
			
		if(strlen(input3)<strlen(input2)){
		char *k=input2;
		char *t=input3;
		input2=t;
		input3=k;}

		//pad '0' 
	
		char *str1; 
		const char *padding="00000000"; 
		const char *myString=input3; 
		int pi_length=strlen(myString); 
		int padLen = pi_length - strlen(myString); 
		str1= (char *)malloc(100*sizeof(char)); 
		sprintf(str1,"%*.*s%s", padLen, padLen, padding, myString);
	
		//or operation
		char *str2; 
		const char *myString1=input2; 
		str2= (char *)malloc(100*sizeof(char));
		int padLen1 = pi_length - strlen(myString1);  
		sprintf(str2,"%*.*s%s", padLen1, padLen1, padding, myString1);

		int length = (int)strlen(str1);
		char str3[10]=""; 
		for (int i = 0; i < length; i++){
			if(str1[i]==48 && str2[i]==48){
				char *a="0";
				strcat(str3,a);
			}
			else{
				char *b="1";
				strcat(str3,b);}
			
		} 
	
	
		char *result=str3;
		while(*result==48){
			result++;
		}
		strcat(output,input2);
		strcat(output," or ");
		strcat(output,input3);
		strcat(output," = ");
		strcat(output,result);
		strcat(output,"\n");

		printf("The computation results are: \n%s or %s = %s\n",input2,input3,result);
		
		while(token!=NULL){
			token = strsep(&buf,"\n");
			i++;
			char c[] = ",";
			char *p = strtok(token,c);
			if(p==NULL){break;}
			char *input1=p;
			p = strtok(NULL,c);
			char *input2=p;
			p = strtok(NULL,c); 
			char *input3=p;

			if(strlen(input3)<strlen(input2)){
			char *k=input2;
			char *t=input3;
			input2=t;
			input3=k;}

			//pad '0' 
	
			char *str1; 
			const char *padding="00000000"; 
			const char *myString=input3; 
			int pi_length=strlen(myString); 
			int padLen = pi_length - strlen(myString); 
			str1= (char *)malloc(100*sizeof(char)); 
			sprintf(str1,"%*.*s%s", padLen, padLen, padding, myString);
	
			//or operation
			char *str2; 
			const char *myString1=input2; 
			str2= (char *)malloc(100*sizeof(char));
			int padLen1 = pi_length - strlen(myString1);  
			sprintf(str2,"%*.*s%s", padLen1, padLen1, padding, myString1);

			int length = (int)strlen(str1);
			char str3[10]=""; 
			for (int i = 0; i < length; i++){
				if(str1[i]==48 && str2[i]==48){
					char *a="0";
					strcat(str3,a);
				}
				else{
					char *b="1";
					strcat(str3,b);}
			
			} 
	
	
			char *result=str3;
			while(*result==48){
				result++;
			}
			strcat(output,input2);
			strcat(output," or ");
			strcat(output,input3);
			strcat(output," = ");
			strcat(output,result);
			strcat(output,"\n");
			printf("%s or %s = %s\n",input2,input3,result);}





		printf("The Server OR has successfully received %d lines from the edge server and finished all OR computation.\n",i);

		
		

		
		n=sendto(sock,output,sizeof(output),0,(struct sockaddr*)&remote,len);
		if(n<0){
			perror("sendto");}
		else{
		printf("The Server OR has successfully finished sending all computation results to the edge server.\n");}
		return 0;
		
		
	}
	
	
}
