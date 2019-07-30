#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<assert.h>
int connect_to_ser();
int main()
{
	int sockfd=connect_to_ser();
	assert(sockfd!=-1);
	while(1)
	{
		char buff[128]={0};

		printf("connect>>");
		fflush(stdout);

		fgets(buff,128,stdin);
		buff[strlen(buff)-1]=0;
		//测试代码
		if(buff[0]==0)
		{
			continue;

		}
		send(sockfd,buff,strlen(buff),0);

		char readbuff[4096]={0};
		read(sockfd,readbuff,4095,0);
		if(strncmp(readbuff,"ok#",3)!=0)
		{
			printf("error!!");

		}
		printf("%s\n",readbuff+3);
	}
	exit(0);
}
/**************
**********************
*stu 5,9,2019,creat_socket()创建套接字
*
*********************************************/
#define     PORT    6000
#define	IPSTR  "127.0.0.1"
#define LIS_MAX 5//listen的值
int connect_to_ser()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		return -1;
	}
	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	saddr.sin_addr.s_addr=inet_addr(IPSTR);

	int res=connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(res ==-1)
	{
		return -1;
	}
	listen(sockfd,LIS_MAX);
	return sockfd;

}
