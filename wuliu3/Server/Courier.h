#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
#include<cstring>
#include "public.h"
using namespace std;

class Courier
{
private:
    string m_username;//�û���
    string m_name;//����
    string m_phone;
    string m_password;//����
    double m_remaining;//���

public:
    Courier();
    ~Courier();
    int LogIn3(SOCKET recvsockCli);//��¼
    void SetCourier(SOCKET recvsockCli);//���ÿ��Ա
    void RemoveCourier(SOCKET recvsockCli) const;//ɾ�����Ա
    void SendDel(SOCKET recvsockCli);//���տ��
    void SearchDel(SOCKET recvsockCli) const;//��ѯ���
    void SearchS0(SOCKET recvsockCli) const;//��ѯ���ʹ�
    void SearchS1(SOCKET recvsockCli) const;//��ѯ������
    void SearchUser1(SOCKET recvsockCli) const;//��ѯ�ļ���
    void SearchUser2(SOCKET recvsockCli) const;//��ѯ�ռ���
    void SearchT1(SOCKET recvsockCli) const;//��ѯ�ļ�ʱ��
    void SearchT2(SOCKET recvsockCli) const;//��ѯ�ռ�ʱ��
    void SearchNum(SOCKET recvsockCli) const;//��ѯ����
    int Count() const;//��ѯ���Ա��Ŀ
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<string>& t_remaining) const;//�ļ��еĿ��Ա��Ϣ
    void SaveInfo() const;//������Ϣ
    void UpdateInfo() const;//������Ϣ
};

