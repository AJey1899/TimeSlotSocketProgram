#include<sys/socket.h>;
#include<stdio.h>;
#include<string.h>;
#include<netdb.h>;;
#include<time.h>;
#include<stdlib.h>;
#include<math.h>;
struct time
{
int hour, minute, second;
};
int main()
{
char buf[100];
int k,buf1=0;
socklen_t len;
int sock_desc,temp_sock_desc;
struct sockaddr_in server,client;

int hr1,min1,sec1,hr2,min2,sec2;
struct time t1, t2, t3;
int seconds1, seconds2, totalSeconds;
memset(&amp;server,0,sizeof(server));
memset(&amp;client,0,sizeof(client));
sock_desc=socket(AF_INET,SOCK_STREAM,0);
if(sock_desc==-1)
{
printf(&quot;Error in socket creation&quot;);
exit(1);
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr(&quot;127.0.0.1&quot;);
server.sin_port=3002;
k=bind(sock_desc,(struct sockaddr*)&amp;server,sizeof(server));

if(k==-1)
{
printf(&quot;Error in binding&quot;);
exit(1);
}
k=listen(sock_desc,20);
if(k==-1)
{
printf(&quot;Error in listening&quot;);
exit(1);
}
len=sizeof(client);
temp_sock_desc=accept(sock_desc,(struct sockaddr*)&amp;client,&amp;len);
if(temp_sock_desc==-1)
{
printf(&quot;Error in temporary socket creation&quot;);
exit(1);
}
while(1)
{
k=recv(temp_sock_desc,buf,100,0);
if(k==-1)
{
printf(&quot;Error in receiving&quot;);
exit(1);
}
printf(&quot;Command got from client PC is : %s\n&quot;,buf);
if(strncmp(buf,&quot;start&quot;,5)==0)
{
time_t my_time;
struct tm * timeinfo;
time (&amp;my_time);
timeinfo = localtime (&amp;my_time);
hr1 = timeinfo-&gt;tm_hour;
min1 = timeinfo-&gt;tm_min;
sec1 = timeinfo-&gt;tm_sec;
printf(&quot;%d:%d:%d\n&quot;,hr1,min1,sec1);
}

else if(strncmp(buf,&quot;stop&quot;,4)==0)
{
time_t mt2;
struct tm *timeinfo1;
time(&amp;mt2);
timeinfo1 = localtime (&amp;mt2);
hr2 = timeinfo1-&gt;tm_hour;
min2 = timeinfo1-&gt;tm_min;
sec2 = timeinfo1-&gt;tm_sec;
printf(&quot;%d:%d:%d\n&quot;,hr2,min2,sec2);
break;
}
}
//Calculates difference between two time values
t1.hour = hr2;
t1.minute = min2;
t1.second = sec2;
t2.hour = hr1;
t2.minute = min1;
t2.second = sec1;
seconds1 = t1.hour*60*60 + t1.minute*60 + t1.second;
seconds2 = t2.hour*60*60 + t2.minute*60 + t2.second;
totalSeconds = seconds1-seconds2;

t3.minute = totalSeconds/60;
t3.hour = t3.minute/60;
t3.minute = t3.minute%60;
t3.second = totalSeconds%60;
printf(&quot;The PC is used for time: %02d:%02d:%02d\n&quot;, t3.hour, t3.minute, t3.second);

/* k=send(temp_sock_desc,buf,100,0);
if(k==-1)
{
printf(&quot;Error in sending&quot;);
exit(1);
}*/
if(t3.hour == 0)

{
if(t3.minute &gt; 40 &amp;&amp; t3.minute &lt;= 59 )
{
buf1 = 20;
}
else if(t3.minute &lt;= 40 &amp;&amp; t3.minute &gt;=10)
{
buf1 = 10;
}
else if(t3.minute &gt;= 0 &amp;&amp; t3.minute &lt;10 )
{
buf1 = 5;
}
}
else if(t3.hour == 1)
{
if(t3.minute &gt; 40 &amp;&amp; t3.minute &lt;= 59 )
{
buf1 = 40;
}
else if(t3.minute &lt;= 40 &amp;&amp; t3.minute &gt;=10)
{
buf1 = 30;
}
else if(t3.minute &gt;= 0 &amp;&amp; t3.minute &lt;10 )
{
buf1 = 20;
}
}
else if(t3.hour == 2)
{
if(t3.minute &gt; 40 &amp;&amp; t3.minute &lt;= 59 )
{
buf1 = 60;
}
else if(t3.minute &lt;= 40 &amp;&amp; t3.minute &gt;=10)
{
buf1 = 50;
}
else if(t3.minute &gt;= 0 &amp;&amp; t3.minute &lt;10 )
{
buf1 = 40;
}

}
k=send(sock_desc,buf1,100,0);
if(k==-1)
{
printf(&quot;Error in sending&quot;);
exit(1);
}
close(temp_sock_desc);
exit(0);
return 0;
}