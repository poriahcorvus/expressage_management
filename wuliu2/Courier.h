#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
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
    int LogIn3();//��¼
    void SetCourier();//���ÿ��Ա
    void RemoveCourier() const;//ɾ�����Ա
    void SendDel();//���տ��
    void SearchDel() const;//��ѯ���
    void SearchS0() const;//��ѯ���ʹ�
    void SearchS1() const;//��ѯ������
    void SearchUser1() const;//��ѯ�ļ���
    void SearchUser2() const;//��ѯ�ռ���
    void SearchT1() const;//��ѯ�ļ�ʱ��
    void SearchT2() const;//��ѯ�ռ�ʱ��
    void SearchNum() const;//��ѯ����
    int Count() const;//��ѯ���Ա��Ŀ
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<double>& t_remaining) const;//�ļ��еĿ��Ա��Ϣ
    void SaveInfo() const;//������Ϣ
    void UpdateInfo() const;//������Ϣ
};

