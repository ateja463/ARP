#include<bits/stdc++.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include<pthread.h>

#define PORT_NO 7687
#define BUF_SIZE 1024

using namespace std;

set <int> cnsfd;
pthread_mutex_t lockm;
void signal_callback_handler(int signum)
{
     
}
void *serv_func(void *param)
{
	signal(SIGPIPE, signal_callback_handler);
	cout <<"in server function"<<endl;

	int nsfd= *(int *) param;
	char buf[BUF_SIZE],buf1[BUF_SIZE];
	while(1)
	{	
		int n=recv(nsfd,buf,BUF_SIZE,0);
		buf[n-1]='\0';	
                cout<<"message from client: "<<buf<<endl;
		if(n==0)
                {
                    cnsfd.erase(nsfd);
                    break;
                }
                pthread_mutex_lock(&lockm);

		pthread_mutex_unlock(&lockm);
		send(nsfd,"serviced\n",sizeof("serviced\n"),0);
		
                signal(SIGPIPE, signal_callback_handler);
	}
        cout<<nsfd<<" is closed\n";
        close(nsfd);			
}

void *broad_cast_serv_func(void *param)
{

     while(1)
     {
          set<int> ::iterator it;
          for(it=cnsfd.begin();it!=cnsfd.end();it++)
          {
               cout<<*it<<endl;
          }
     }
}
int main(int argc,char **argv)
{
	pthread_t tid[BUF_SIZE];
        pthread_t broad_cast;
        pthread_create(&broad_cast,NULL,broad_cast_serv_func,NULL);
	int i=0,n;	
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		cout<<"socket creation error\n";
	}
	else
	{	cout<<"socket creation successful\n";
		struct sockaddr_in serv_addr,client_addr;
		serv_addr.sin_family=AF_INET;
		serv_addr.sin_port=htons(PORT_NO);
		serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		n=bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
		if(n==-1) 
		{
			cout<<"bind error\n";
		}
		else 
		{
			cout<<"bind successful\n";
			n=listen(sfd,8);
			if(n==-1) 
			{

				cout<<"listen error\n";
			}
			else
			{
				socklen_t addr_size;
				while(1)
				{
					int nsfd=accept(sfd,(struct sockaddr *) & client_addr,&addr_size);
					cout <<"accept return " <<nsfd<<endl;
					if(nsfd==-1)
					{
						cout<<"accept error\n";
					}
					else
					{
                                                
                                                cnsfd.insert(nsfd);
						cout<<"accept successful\n";
						cout <<"before calling thread"<<endl;
                                                
						if(i<BUF_SIZE)
						{
						    pthread_create(&tid[i++],NULL,serv_func,(void *)&nsfd);
						}
					}
				}
			}
		}
	}
}






