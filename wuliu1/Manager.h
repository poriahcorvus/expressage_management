#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
using namespace std;

class Manager
{
    //friend void Users::ExpressDel();
private:
    string m_username;
    string m_name;
    string m_password;
    double m_remaining;
public:
    Manager();
    ~Manager();
    int LogIn2();
    void UsInfo() const;//�鿴�����û���Ϣ
    void ObInfo() const;//�鿴���п����Ϣ
    void SearchInfo() const;//��ѯ
    void SearchUser() const;//��ѯ�û�
    void SearchNumber() const;//��ѯ��ݵ���
    void SearchTime_1() const;//��ѯ����ʱ��
    void SearchTime_2() const;//��ѯǩ��ʱ��
    //void RemainAdd();//����
    void UpdateRemain() const;//����
    //void SignUpMess();//���ù���Ա��Ϣ
    //int UserSum();//�û�����
    //int ObjSum();//�������
};

