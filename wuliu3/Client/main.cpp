#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <cstring>
#include <string>
using namespace std;

int main()
{
	cout << "---------------客户端--------------" << endl;

	//加载socket库
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		//输出出错信息
		cout << "载入socket库失败" << endl;
		system("pause");
		return 0;
	}

	//创建socket
	SOCKET sockCli;
	sockCli = socket(AF_INET, SOCK_STREAM, 0);//AF是地址描述；type指定socket类型；protocol指定协议，不指定为0
	if (SOCKET_ERROR == sockCli) {
		cout << "套接字创建失败" << endl;
		return 0;
	}

	//初始化地址
	sockaddr_in addrCli;
	addrCli.sin_family = AF_INET;
	addrCli.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrCli.sin_port = htons(44444);
	//绑定socket和本地地址
	int cRes = connect(sockCli, (SOCKADDR*)&addrCli, sizeof(SOCKADDR));
	if (SOCKET_ERROR == cRes) {
		cout << "客户端与服务器连接失败" << endl;
		return 0;
	}

	while (1) {

		/*
		string recvBuf;
		int reLen = recv(sockCli, (char*)recvBuf.c_str(), recvBuf.length(), 0);
		cout << recvBuf << endl;
		*/

		char recvBuf[2048] = {};
		char sendBuf[2048] = {};
		int reLen = SOCKET_ERROR;
		int sLen = SOCKET_ERROR;
		reLen = recv(sockCli, recvBuf, sizeof(recvBuf), 0);
		if (strcmp(recvBuf, "close the connect") == 0)
			break;
		else {
			cout << recvBuf;
			reLen = SOCKET_ERROR;
			reLen = recv(sockCli, recvBuf, sizeof(recvBuf), 0);
			if (strcmp(recvBuf, "1") == 0) {
				cin.getline(sendBuf, 2048);
				sLen = send(sockCli, sendBuf, sizeof(sendBuf), 0);
				sLen = SOCKET_ERROR;
			}
			reLen = SOCKET_ERROR;

		}
	}

	closesocket(sockCli);

	WSACleanup();

	cout << "客户端已退出" << endl;
	return 0;

}