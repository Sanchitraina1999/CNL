#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main()
{
	int serverfd;
	serverfd=socket(AF_INET,SOCK_DGRAM,0);
	socklen_t len;
	struct sockaddr_in serv;

	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=INADDR_ANY;
	serv.sin_port=htons(8888);

	len=sizeof(serv);
	if(bind(serverfd,(struct sockaddr *)&serv,len)<0)
		cout<<"Not binded with the port(change the port number)"<<endl;
	else
		cout<<"Binded with the port number"<<endl;

	char buffer[100];
	recvfrom(serverfd,buffer,sizeof(buffer),0,(struct sockaddr *)&serv,&len);
	cout<<buffer<<endl;
	char hello[]="Hello from server";
	sendto(serverfd,hello,sizeof(hello),0,(struct sockaddr *)&serv,len);

	char filename[100];
	recvfrom(serverfd,filename,sizeof(filename),0,(struct sockaddr *)&serv,&len);
	string filen="";
	for(int i=0;i<strlen(filename);i++)
		filen+=filename[i];
	
	fstream f;
	f.open(filen,ios::out);
	char filecontent[100];
	recvfrom(serverfd,filecontent,sizeof(filecontent),0,(struct sockaddr *)&serv,&len);
	f<<filecontent;
	cout<<filecontent<<endl;

}