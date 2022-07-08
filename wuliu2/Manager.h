#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
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
    int LogIn2();
    void UsInfo() const;//�鿴�����û���Ϣ
    void ObInfo() const;//�鿴���п����Ϣ
    void CoInfo() const;//�鿴���п��Ա��Ϣ
    void SearchInfo() const;//��ѯ
    void SearchUser() const;//��ѯ�û�
    void SearchExpress() const;//��ѯ�ļ���
    void SearchReceive() const;//��ѯ������
    void SearchT1() const;//��ѯ�ļ�ʱ��
    void SearchT2() const;//��ѯ�ռ�ʱ��
    void SearchCourier() const;//��ѯ���Ա
    void SearchNum() const;//��ѯ��ݵ���
    //void SearchNumber();//��ѯ��ݵ���
    //void SearchTime_1();//��ѯ����ʱ��
    //void SearchTime_2();//��ѯǩ��ʱ��
    //void RemainAdd();//����
    void UpdateRemain(double price) const;//�������
    //void SignUpMess();//���ù���Ա��Ϣ
    //int UserSum();//�û�����
    //int ObjSum();//�������
    void ManageCour() const;//������Ա
    void AllotCour() const;//������Ա
};

