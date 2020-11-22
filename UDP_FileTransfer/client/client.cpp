#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main()
{
	int clientfd;
	clientfd=socket(AF_INET,SOCK_DGRAM,0);
	socklen_t len;
	struct sockaddr_in client;

	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=htons(8888);

	len=sizeof(client);

	char hello[]="Hello from client";
	sendto(clientfd,hello,sizeof(hello),0,(struct sockaddr *)&client,len);
	char buffer[100];
	recvfrom(clientfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&len);
	cout<<buffer<<endl;

	fstream f;
	cout<<"Enter the name of the file: ";
	string file;
	cin>>file;
	char filename[100];
	strcpy(filename,file.c_str());
	sendto(clientfd,filename,sizeof(filename),0,(struct sockaddr *)&client,len);

	f.open("uefa.txt",ios::in);
	string s="";
	while(!f.eof())
	{
		string l="";
		getline(f,l);
		s+=l;
		s+="\n";
	}
	char filecontent[100];
	strcpy(filecontent,s.c_str());
	sendto(clientfd,filecontent,sizeof(filecontent),0,(struct sockaddr *)&client,len);

}