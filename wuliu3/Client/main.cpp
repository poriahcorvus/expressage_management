#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <cstring>
#include <string>
using namespace std;

int main()
{
	cout << "---------------�ͻ���--------------" << endl;

	//����socket��
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		//���������Ϣ
		cout << "����socket��ʧ��" << endl;
		system("pause");
		return 0;
	}

	//����socket
	SOCKET sockCli;
	sockCli = socket(AF_INET, SOCK_STREAM, 0);//AF�ǵ�ַ������typeָ��socket���ͣ�protocolָ��Э�飬��ָ��Ϊ0
	if (SOCKET_ERROR == sockCli) {
		cout << "�׽��ִ���ʧ��" << endl;
		return 0;
	}

	//��ʼ����ַ
	sockaddr_in addrCli;
	addrCli.sin_family = AF_INET;
	addrCli.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrCli.sin_port = htons(44444);
	//��socket�ͱ��ص�ַ
	int cRes = connect(sockCli, (SOCKADDR*)&addrCli, sizeof(SOCKADDR));
	if (SOCKET_ERROR == cRes) {
		cout << "�ͻ��������������ʧ��" << endl;
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

	cout << "�ͻ������˳�" << endl;
	return 0;

}