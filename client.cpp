#include<bits/stdc++.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>

using namespace std;

#define PORT_NO 7687
#define BUF_SIZE 1024

int sfd,ip;
char mac;
void signal_callback_handler(int signum)
{
	close(sfd);
	exit(-1);
}

int main(int argc,char **argv)
{
	signal(SIGINT, signal_callback_handler);
	sfd=socket(AF_INET,SOCK_STREAM,0);	
	struct sockaddr_in client_addr;
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(PORT_NO);
	client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sfd,(struct sockaddr *)& client_addr,sizeof(client_addr));
        char buf[BUF_SIZE];
        int n;
        n=send(sfd,"hii from client\n",sizeof("hii from client\n"),0);
        n=recv(sfd,buf,BUF_SIZE,0);
        cout<<"message from server "<<buf<<endl;
	while(1)
	{
                cout<<"enter message\n";
                n=read(0,buf,20);
		buf[n]='\0';
		n=send(sfd,buf,sizeof(buf),0);
		if(n==-1) break;
		n=recv(sfd,buf,BUF_SIZE,0);
		if(n==-1) break;
		cout<<"message from server "<<buf<<endl;
	}	
}

