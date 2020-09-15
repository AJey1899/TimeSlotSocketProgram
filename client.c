#include<sys/socket.h>;
#include<stdio.h>;
#include<string.h>;
#include<netdb.h>;
#include<stdlib.h>;
int main()
{
char buf[100];
int buf1=0;
int k,z;
int sock_desc,temp_sock_desc;
struct sockaddr_in client;
memset(&amp;client,0,sizeof(client));
sock_desc=socket(AF_INET,SOCK_STREAM,0);
if(sock_desc==-1)
{
printf(&quot;Error in socket creation&quot;);
exit(1);
}
client.sin_family=AF_INET;
client.sin_addr.s_addr=INADDR_ANY;
client.sin_port=3002;
k=connect(sock_desc,(struct sockaddr*)&amp;client,sizeof(client));

if(k==-1)
{
printf(&quot;Error in connecting to server&quot;);
exit(1);
}
while(1)
{
printf(&quot;\nEnter command to be send to server: &quot;);
fgets(buf,100,stdin);
if(strncmp(buf,&quot;end&quot;,3)==0)
break;
k=send(sock_desc,buf,100,0);
if(k==-1)
{
printf(&quot;Error in sending&quot;);
exit(1);
}
if(strncmp(buf,&quot;stop&quot;,4)==0)
{
break;
}
}

z=recv(sock_desc,buf1,100,0);
if(z==-1)
{
printf(&quot;Error in receiving&quot;);
exit(1);
}
printf(&quot;Please pay amount of Rs.%d at the counter&quot;,buf1);
close(sock_desc);
exit(0);
return 0;
}