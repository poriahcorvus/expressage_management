#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
using namespace std;

class Objects
{
    friend class Users;
    friend class Manager;
private:
    string m_number;//��ݵ��ţ�ʱ��+���
    string m_time1;//����ʱ��
    string m_time2;//����ʱ��
    string m_user1;//�ļ��û�
    string m_user2;//�ռ��û�
    int m_state;//��Ʒ״̬��0-��ǩ�գ� 1-��ǩ��
    string m_description;//��Ʒ����

public:
    Objects();
    ~Objects();
    //void SetObjects();//������Ʒ��Ϣ
    string GetNum() const;//��ȡ����
    string GetTime() const;//����ϵͳʱ��
    void MyExpress(string username) const;//�Ҽĳ���
    void MyReceive(string username) const;//�ĸ��ҵ�
    void SearchNumber(string username) const;//��ѯ��ݵ���
    void SearchTime1(string username) const;//��ѯ����ʱ��
    void SearchTime2(string username) const;//��ѯǩ��ʱ��
    void SaveObjects() const;//������Ʒ��Ϣ
    void UpdateObjects() const;//������Ʒ��Ϣ
    void ShowObjects(vector<string>& t_number, vector<string>& t_user1, vector<string>& t_user2, vector<int>& t_state, vector<string>& t_time1, vector<string>& t_time2, vector<string>& t_description) const;//��Ʒ��Ϣ
    int CountObjects() const;//��ݸ���
};

