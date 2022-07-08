#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
#include<cstring>
using namespace std;

class Manager
{
private:
    string m_username;
    string m_name;
    string m_password;
    double m_remaining;
public:
    Manager();
    ~Manager();
    int LogIn2(SOCKET recvsockCli);
    void UsInfo(SOCKET recvsockCli) const;//�鿴�����û���Ϣ
    void ObInfo(SOCKET recvsockCli) const;//�鿴���п����Ϣ
    void CoInfo(SOCKET recvsockCli) const;//�鿴���п��Ա��Ϣ
    void SearchInfo(SOCKET recvsockCli) const;//��ѯ
    void SearchUser(SOCKET recvsockCli) const;//��ѯ�û�
    void SearchExpress(SOCKET recvsockCli) const;//��ѯ�ļ���
    void SearchReceive(SOCKET recvsockCli) const;//��ѯ������
    void SearchT1(SOCKET recvsockCli) const;//��ѯ�ļ�ʱ��
    void SearchT2(SOCKET recvsockCli) const;//��ѯ�ռ�ʱ��
    void SearchCourier(SOCKET recvsockCli) const;//��ѯ���Ա
    void SearchNum(SOCKET recvsockCli) const;//��ѯ��ݵ���
    //void SearchNumber();//��ѯ��ݵ���
    //void SearchTime_1();//��ѯ����ʱ��
    //void SearchTime_2();//��ѯǩ��ʱ��
    //void RemainAdd();//����
    void UpdateRemain(double price, SOCKET recvsockCli) const;//�������
    //void SignUpMess();//���ù���Ա��Ϣ
    //int UserSum();//�û�����
    //int ObjSum();//�������
    void ManageCour(SOCKET recvsockCli) const;//������Ա
    void AllotCour(SOCKET recvsockCli) const;//Ϊ��ݷ�����Ա
};

