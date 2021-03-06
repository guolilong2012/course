#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 5050
#define DEFAULT_PORT1 5051

typedef struct {
	char name[40];
	char director[60];
	char year[30];

} List;
List li[100];

int udp_client(char *y)
{
	FILE *pFile;
	pFile = fopen("movielist.txt", "r");
	int flag;
	int cPort = DEFAULT_PORT1;
	int cClient = 0;
	unsigned int cLen = 0;
	int cSend = 0;
	int cRecv = 0;
	char send_buf[4096] = { 0 };
	char recv_buf[4096] = { 0 };
	struct sockaddr_in cli;

	memset(recv_buf, 0, sizeof(recv_buf));

	cli.sin_family = AF_INET;
	cli.sin_port = htons(cPort);
	cli.sin_addr.s_addr = inet_addr(y);

	cClient = socket(AF_INET, SOCK_DGRAM, 0);
	if (cClient < 0) {
		printf("socket() failure!\n");
		return -1;
	}

	cLen = sizeof(cli);

	if (fgets(send_buf, sizeof(send_buf), pFile) != NULL)
		if (fgets(send_buf, sizeof(send_buf), pFile) != NULL)
			cSend =
			    sendto(cClient, send_buf, sizeof(send_buf), 0,
				   (struct sockaddr *) &cli, cLen);
	if ((cSend < 0) || (cSend == 0)) {
		printf("sendto() failure!\n");
		return -1;
	} else {
		printf("sendto() succeeded.\n");
	}

	cRecv =
	    recvfrom(cClient, recv_buf, sizeof(recv_buf), 0,
		     (struct sockaddr *) &cli, (unsigned int *) &cLen);
	if ((cRecv < 0) || (cRecv == 0)) {
		printf("recvfrom() failure!\n");
		return -1;
	}
	if (strcmp(recv_buf, "The Movielist.txt is not changed!") == 0)
		flag = 0;
	if (strcmp(recv_buf, "The Movielist.txt is changed!") == 0)
		flag = 1;
	if (flag == 0)
		printf("目前没有更新!\n");
	if (flag == 1)
		printf("已有更新,请重新下载!\n");
	fclose(pFile);
	close(cClient);
	printf("\n");
	return 0;
}

int tcp_client(char *y)
{
	FILE *pFile;
	int cPort = DEFAULT_PORT;
	int cClient = 0;
	int cLen = 0;
	char cbuf[1024] = { 0 };
	struct sockaddr_in cli;

	memset(cbuf, 0, sizeof(cbuf));

	cli.sin_family = AF_INET;	//IPv4 Internet protocols
	cli.sin_port = htons(cPort);
	cli.sin_addr.s_addr = inet_addr(y);
	pFile = fopen("movielist.txt", "w");

	while (1) {

		cClient = socket(AF_INET, SOCK_STREAM, 0);

		if (cClient < 0) {
			printf("socket() failure!\n");
			return -1;
		}

		if (connect(cClient, (struct sockaddr *) &cli, sizeof(cli)) < 0)	//成功返回0
		{
			printf("connect() failure!\n");
			return -1;
		}

		cLen = recv(cClient, cbuf, sizeof(cbuf), 0);

		if ((cLen < 0) || (cLen == 0)) {
			break;
		}
		if (strncmp(cbuf, "the end of the file!", 20) == 0)
			break;
		fputs(cbuf, pFile);
	}
	fclose(pFile);
	close(cClient);
	printf("下载成功\n");
	printf("\n");
	return 0;
}

void get_Movielist(char cbuf[])
{
	static int i = 0;

	if (strncmp(cbuf, "Name @:", 7) == 0) {
		strcpy(li[i].name, cbuf);
	}

	if (strncmp(cbuf, "Director @:", 11) == 0) {
		strcpy(li[i].director, cbuf);
	}

	if (strncmp(cbuf, "Year @:", 7) == 0) {
		strcpy(li[i].year, cbuf);
		i++;
	}

}

int listName()
{
	int i;
	for (i = 0; i < 100; i++)
		printf("%s", li[i].name);
	printf("\n");
	return 0;
}

int listDirector()
{
	int i, j;
	printf("%s", li[0].director);
	for (j = 0; j < 10; j++)
		for (i = j - 1; i >= 0; i--) {
			if (strcmp(li[j].director, li[i].director) == 0)
				break;
			if (i == 0)
				printf("%s", li[j].director);
		}
	printf("\n");
	return 0;
}

int accordingtoYear()
{
	int m;
	char a[20] = "Year @: ";
	char s[10];

	printf("Input the year:");
	scanf("%s", s);
	strcat(a, s);
	for (m = 0; m < 100; m++) {

		if (strncmp(li[m].year, a, 12) == 0) {

			printf("%s", li[m].name);
			printf("%s", li[m].director);

		}
	}
	printf("\n");
	return 0;
}

int accordingtoDirector()
{
	int i;
	char b[40] = "Director @: ";
	char s[20];
	printf("Input the Director_name:");
	scanf("%s", s);
	strcat(b, s);

	for (i = 0; i < 100; i++) {
		if (strncmp(li[i].director, b, strlen(b)) == 0) {
			printf("%s", li[i].name);
			printf("%s", li[i].year);
		}
	}
	printf("\n");
	return 0;

}

int display()
{
	int i;
	for (i = 0; i < 100; i++) {
		printf("%s", li[i].name);
		printf("%s", li[i].director);
		printf("%s", li[i].year);
	}
	printf("\n");
	return 0;
}

int jiexi()
{
	int a;
	char cbuf[1024] = { 0 };
	FILE *pFile = fopen("movielist.txt", "r");
	while (!feof(pFile)) {
		cbuf[0] = '\0';
		fgets(cbuf, sizeof(cbuf), pFile);

		get_Movielist(cbuf);
	}

	while (1) {
		printf("1.listName\n");
		printf("2.listDirector\n");
		printf("3.accordingtoYear\n");
		printf("4.accordingtoDirector\n");
		printf("5.Display all\n");
		printf("6.Exit\n");
		printf("Please choose:");
		scanf("%d", &a);
		switch (a) {
		case 1:
			listName();
			break;

		case 2:
			listDirector();
			break;

		case 3:
			accordingtoYear();
			break;

		case 4:
			accordingtoDirector();
			break;

		case 5:
			display();
			break;
		case 6:
			return -1;
		default:
			break;
		}

	}
	return 0;
}

int main(int argc, char *argv[])
{
	int c;
	char s[20] = { 0 };
	while (1) {
		printf("1.检查是否更新\n");
		printf("2.下载\n");
		printf("3.解析\n");
		printf("4.退出\n");
		printf("Please choose:");
		scanf("%d", &c);

		switch (c) {
		case 1:
			printf("\n请输入IP：");
			scanf("%s", s);
			udp_client(s);
			break;
		case 2:
			printf("\n请输入IP：");
			scanf("%s", s);
			tcp_client(s);
			break;
		case 3:
			jiexi();
			break;
		case 4:
			exit(0);
		default:
			break;

		}
	}
	return 0;
}
