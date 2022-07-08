#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
using namespace std;

class Users
{
    friend class Manager;
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
    int LogIn1();//��¼
    void SignUp();//ע��
    void SetMess();//������Ϣ
    void ChangePass();//��������
    void CheckRemain() const;//��ѯ�˻����
    void TopUp();//�˻���ֵ
    void ExpressDel();//�Ŀ��
    void ReceiveDel() const;//�տ��
    void SearchDel() const;//��ѯ���
    int Count() const;//��ѯ��ע���û���
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<double>& t_remaining, vector<string>& t_address) const;//�ļ��е��û���Ϣ
    void SaveInfo() const;//������Ϣ
    void UpdateInfo() const;//������Ϣ
};

