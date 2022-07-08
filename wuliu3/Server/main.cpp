#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <cstring>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>

#include "Manager.h"
#include "Courier.h"
#include "Users.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"
#include "public.h"

using namespace std;


int main()
{
	cout << "--------------������--------------" << endl;

	//����socket��
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		//���������Ϣ
		cout << "����socket��ʧ��" << endl;
		return 0;
	}

	//����socket
	SOCKET sockSer;
	sockSer = socket(AF_INET, SOCK_STREAM, 0);//AF�ǵ�ַ������typeָ��socket���ͣ�protocolָ��Э�飬��ָ��Ϊ0
	if (SOCKET_ERROR == sockSer) {
		cout << "�׽��ִ���ʧ��" << endl;
		return 0;
	}
	//��ʼ����ַ
	sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSer.sin_port = htons(44444);

	//��socket�ͱ��ص�ַ
	int bRes = bind(sockSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));
	if (SOCKET_ERROR == bRes) {
		cout << "��ʧ��" << endl;
		return 0;
	}

	int lLen = listen(sockSer, 5);
	if (SOCKET_ERROR == lLen) {
		cout << "����ʧ��" << endl;
		return 0;
	}

	sockaddr_in recvaddrCli;
	SOCKET recvsockCli = INVALID_SOCKET;
	int _revSize = sizeof(sockaddr_in);
	recvsockCli = accept(sockSer, (SOCKADDR*)&recvaddrCli, &_revSize);
	if (INVALID_SOCKET == recvsockCli) {
		cout << "�������˽�������ʧ��" << endl;
		return 0;
	}
	else
		cout << "�������˽�������ɹ�" << endl;

	while (1) {
		char sendBuf[SIZE] = "\n��ӭʹ����������ϵͳ��\n��ѡ��������ݣ�\n1 - ����Ա\n2 - ��ͨ�û�\n3 - ���Ա\n0 - �˳�\n";
		cout << sendBuf;
		int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
		sLen = SOCKET_ERROR;
		strcpy(sendBuf, "1");
		sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);

		if (SOCKET_ERROR == sLen) {
			cout << "�������˷�������ʧ��" << endl;
			return 0;
		};
		sLen = SOCKET_ERROR;

		char recvBuf[SIZE] = {};
		int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
		cout << recvBuf << endl;

		int identity, choice, op, l;
		identity = atoi(recvBuf);
		reLen = SOCKET_ERROR;

		if (identity)
			strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����");
		else {
			strcpy(sendBuf, "close the connect");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			break;
		}
		if (identity == 1) {
			strcat(sendBuf, "\n1 - ��¼\n0 - �˳�\n");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			cout << sendBuf;
			sLen = SOCKET_ERROR;

			strcpy(sendBuf, "1");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			sLen = SOCKET_ERROR;

			reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
			cout << recvBuf;
			choice = atoi(recvBuf);
			reLen = SOCKET_ERROR;

			if (choice == 1) {
				Manager manager;
				l = manager.LogIn2(recvsockCli);
				if (l == 1) {
					strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����\n1 - ��ѯ\n2 - ������Ա\n3 - Ϊ���ָ�ɿ��Ա\n0 - �˳�\n");
					cout << sendBuf;
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;

					strcpy(sendBuf, "1");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;

					reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
					cout << recvBuf;
					op = atoi(recvBuf);
					reLen = SOCKET_ERROR;

					while (op) {

						if (op == 1)
							manager.SearchInfo(recvsockCli);
						else if (op == 2)
							manager.ManageCour(recvsockCli);
						else if (op == 3)
							manager.AllotCour(recvsockCli);
						else {
							strcpy(sendBuf, "\n������Ϸ��Ĳ�����\n");
							cout << sendBuf;
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;

							strcpy(sendBuf, "0");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;
						}

						strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����\n1 - ��ѯ\n2 - ������Ա\n3 - Ϊ���ָ�ɿ��Ա\n0 - �˳�\n");
						cout << sendBuf;
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;

						strcpy(sendBuf, "1");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;

						reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
						cout << recvBuf;
						op = atoi(recvBuf);
						reLen = SOCKET_ERROR;

					}
					if (op == 0) {
						strcpy(sendBuf, "close the connect");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;
						break;
					}
				}
				else {
					strcpy(sendBuf, "close the connect");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;
					break;
				}
			}
			else {
				strcpy(sendBuf, "close the connect");
				sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
				sLen = SOCKET_ERROR;
				break;
			}
		}
		if (identity == 2) {
			strcat(sendBuf, "\n1 - ��¼\n2 - ���û�ע��\n0 - �˳�\n");
			cout << sendBuf;
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			sLen = SOCKET_ERROR;

			strcpy(sendBuf, "1");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			sLen = SOCKET_ERROR;

			reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
			cout << recvBuf;
			choice = atoi(recvBuf);
			reLen = SOCKET_ERROR;

			if (choice == 1 || choice == 2) {
				Users user;
				if (choice == 2)
					user.SignUp(recvsockCli);
				l = user.LogIn1(recvsockCli);
				if (l == 1) {
					strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����\n1 - �޸�����\n2 - ��ѯ�˻����\n3 - �˻���ֵ\n4 - �ļ�\n5 - ȡ��\n6 - ��ѯ���\n0 - �˳�\n");
					cout << sendBuf;
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;

					strcpy(sendBuf, "1");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;

					reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
					cout << recvBuf;
					op = atoi(recvBuf);
					reLen = SOCKET_ERROR;

					while (op) {

						if (op == 1)
							user.ChangePass(recvsockCli);
						else if (op == 2)
							user.CheckRemain(recvsockCli);
						else if (op == 3)
							user.TopUp(recvsockCli);
						else if (op == 4)
							user.ExpressDel(recvsockCli);
						else if (op == 5)
							user.ReceiveDel(recvsockCli);
						else if (op == 6)
							user.SearchDel(recvsockCli);
						else {
							strcpy(sendBuf, "\n������Ϸ�������\n");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							cout << sendBuf;
							sLen = SOCKET_ERROR;

							strcpy(sendBuf, "0");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;
						}

						strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����\n1 - �޸�����\n2 - ��ѯ�˻����\n3 - �˻���ֵ\n4 - �ļ�\n5 - ȡ��\n6 - ��ѯ���\n0 - �˳�\n");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						cout << sendBuf;
						sLen = SOCKET_ERROR;

						strcpy(sendBuf, "1");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;

						reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
						cout << recvBuf;
						op = atoi(recvBuf);
						reLen = SOCKET_ERROR;

					}
					if (op == 0) {
						strcpy(sendBuf, "close the connect");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;
						break;
					}
				}
				else {
					strcpy(sendBuf, "close the connect");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;
					break;
				}
			}
			else {
				strcpy(sendBuf, "close the connect");
				sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
				sLen = SOCKET_ERROR;
				break;
			}
		}

		if (identity == 3) {
			strcat(sendBuf, "\n1 - ��¼\n0 - �˳�\n");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			cout << sendBuf;

			strcpy(sendBuf, "1");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			sLen = SOCKET_ERROR;

			reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
			cout << recvBuf;
			choice = atoi(recvBuf);
			reLen = SOCKET_ERROR;

			if (choice == 1) {
				Courier courier;
				l = courier.LogIn3(recvsockCli);
				if (l == 1) {
					strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����\n1 - ���տ��\n2 - ��ѯ\n0 - �˳�\n");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					cout << sendBuf;
					sLen = SOCKET_ERROR;

					strcpy(sendBuf, "1");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;

					reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
					cout << recvBuf;
					op = atoi(recvBuf);
					reLen = SOCKET_ERROR;

					while (op) {
						if (op == 1)
							courier.SendDel(recvsockCli);
						else if (op == 2)
							courier.SearchDel(recvsockCli);
						else {
							strcpy(sendBuf, "\n������Ϸ�������\n");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							cout << sendBuf;
							sLen = SOCKET_ERROR;

							strcpy(sendBuf, "0");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;
						}

						strcpy(sendBuf, "\n��ѡ�������Ҫִ�еĲ�����\n1 - ���տ��\n2 - ��ѯ\n0 - �˳�\n");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						cout << sendBuf;
						sLen = SOCKET_ERROR;

						strcpy(sendBuf, "1");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;

						reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
						cout << recvBuf;
						op = atoi(recvBuf);
						reLen = SOCKET_ERROR;
					}
					if (op == 0) {
						strcpy(sendBuf, "close the connect");
						sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
						sLen = SOCKET_ERROR;
						break;
					}
				}
				else {
					strcpy(sendBuf, "close the connect");
					sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
					sLen = SOCKET_ERROR;
					break;
				}
			}
			else {
				strcpy(sendBuf, "close the connect");
				sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
				sLen = SOCKET_ERROR;
				break;
			}
		}
	}

	closesocket(recvsockCli);
	closesocket(sockSer);

	WSACleanup();

	cout << "�������ѹر�" << endl;

	return 0;
}