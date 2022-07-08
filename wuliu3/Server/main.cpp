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
	cout << "--------------服务器--------------" << endl;

	//加载socket库
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		//输出出错信息
		cout << "载入socket库失败" << endl;
		return 0;
	}

	//创建socket
	SOCKET sockSer;
	sockSer = socket(AF_INET, SOCK_STREAM, 0);//AF是地址描述；type指定socket类型；protocol指定协议，不指定为0
	if (SOCKET_ERROR == sockSer) {
		cout << "套接字创建失败" << endl;
		return 0;
	}
	//初始化地址
	sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSer.sin_port = htons(44444);

	//绑定socket和本地地址
	int bRes = bind(sockSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));
	if (SOCKET_ERROR == bRes) {
		cout << "绑定失败" << endl;
		return 0;
	}

	int lLen = listen(sockSer, 5);
	if (SOCKET_ERROR == lLen) {
		cout << "监听失败" << endl;
		return 0;
	}

	sockaddr_in recvaddrCli;
	SOCKET recvsockCli = INVALID_SOCKET;
	int _revSize = sizeof(sockaddr_in);
	recvsockCli = accept(sockSer, (SOCKADDR*)&recvaddrCli, &_revSize);
	if (INVALID_SOCKET == recvsockCli) {
		cout << "服务器端接受请求失败" << endl;
		return 0;
	}
	else
		cout << "服务器端接受请求成功" << endl;

	while (1) {
		char sendBuf[SIZE] = "\n欢迎使用物流管理系统！\n请选择您的身份：\n1 - 管理员\n2 - 普通用户\n3 - 快递员\n0 - 退出\n";
		cout << sendBuf;
		int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
		sLen = SOCKET_ERROR;
		strcpy(sendBuf, "1");
		sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);

		if (SOCKET_ERROR == sLen) {
			cout << "服务器端发送数据失败" << endl;
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
			strcpy(sendBuf, "\n请选择接下来要执行的操作：");
		else {
			strcpy(sendBuf, "close the connect");
			sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
			break;
		}
		if (identity == 1) {
			strcat(sendBuf, "\n1 - 登录\n0 - 退出\n");
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
					strcpy(sendBuf, "\n请选择接下来要执行的操作：\n1 - 查询\n2 - 管理快递员\n3 - 为快递指派快递员\n0 - 退出\n");
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
							strcpy(sendBuf, "\n请输入合法的操作！\n");
							cout << sendBuf;
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;

							strcpy(sendBuf, "0");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;
						}

						strcpy(sendBuf, "\n请选择接下来要执行的操作：\n1 - 查询\n2 - 管理快递员\n3 - 为快递指派快递员\n0 - 退出\n");
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
			strcat(sendBuf, "\n1 - 登录\n2 - 新用户注册\n0 - 退出\n");
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
					strcpy(sendBuf, "\n请选择接下来要执行的操作：\n1 - 修改密码\n2 - 查询账户余额\n3 - 账户充值\n4 - 寄件\n5 - 取件\n6 - 查询快递\n0 - 退出\n");
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
							strcpy(sendBuf, "\n请输入合法操作！\n");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							cout << sendBuf;
							sLen = SOCKET_ERROR;

							strcpy(sendBuf, "0");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;
						}

						strcpy(sendBuf, "\n请选择接下来要执行的操作：\n1 - 修改密码\n2 - 查询账户余额\n3 - 账户充值\n4 - 寄件\n5 - 取件\n6 - 查询快递\n0 - 退出\n");
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
			strcat(sendBuf, "\n1 - 登录\n0 - 退出\n");
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
					strcpy(sendBuf, "\n请选择接下来要执行的操作：\n1 - 揽收快递\n2 - 查询\n0 - 退出\n");
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
							strcpy(sendBuf, "\n请输入合法操作！\n");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							cout << sendBuf;
							sLen = SOCKET_ERROR;

							strcpy(sendBuf, "0");
							sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
							sLen = SOCKET_ERROR;
						}

						strcpy(sendBuf, "\n请选择接下来要执行的操作：\n1 - 揽收快递\n2 - 查询\n0 - 退出\n");
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

	cout << "服务器已关闭" << endl;

	return 0;
}