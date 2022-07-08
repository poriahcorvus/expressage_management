#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
#include "Objects.h"
using namespace std;

class Users
{
private:
    string m_username;//�û���
    string m_name;//����
    string m_phone;//�绰
    string m_password;//����
    double m_remaining;//�˻����
    string m_address;//��ַ

public:
    Users();
    ~Users();
    int LogIn1(SOCKET recvsockCli);//��¼
    void SignUp(SOCKET recvsockCli);//ע��
    void SetMess(SOCKET recvsockCli);//������Ϣ
    void ChangePass(SOCKET recvsockCli);//��������
    void CheckRemain(SOCKET recvsockCli) const;//��ѯ�˻����
    void TopUp(SOCKET recvsockCli);//�˻���ֵ
    void ExpressDel(SOCKET recvsockCli);//�Ŀ��
    void Express(Objects& ob, SOCKET recvsockCli);
    void ReceiveDel(SOCKET recvsockCli) const;//�տ��
    void SearchDel(SOCKET recvsockCli) const;//��ѯ���
    int Count() const;//��ѯ��ע���û���
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<string>& t_remaining, vector<string>& t_address) const;//�ļ��е��û���Ϣ
    void SaveInfo(SOCKET recvsockCli) const;//������Ϣ
    void UpdateInfo() const;//������Ϣ
};

