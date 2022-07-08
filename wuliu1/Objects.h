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
    string m_number;//快递单号：时间+编号
    string m_time1;//寄送时间
    string m_time2;//接收时间
    string m_user1;//寄件用户
    string m_user2;//收件用户
    int m_state;//物品状态：0-已签收， 1-待签收
    string m_description;//物品描述

public:
    Objects();
    ~Objects();
    //void SetObjects();//设置物品信息
    string GetNum() const;//获取单号
    string GetTime() const;//返回系统时间
    void MyExpress(string username) const;//我寄出的
    void MyReceive(string username) const;//寄给我的
    void SearchNumber(string username) const;//查询快递单号
    void SearchTime1(string username) const;//查询发送时间
    void SearchTime2(string username) const;//查询签收时间
    void SaveObjects() const;//保存物品信息
    void UpdateObjects() const;//更新物品信息
    void ShowObjects(vector<string>& t_number, vector<string>& t_user1, vector<string>& t_user2, vector<int>& t_state, vector<string>& t_time1, vector<string>& t_time2, vector<string>& t_description) const;//物品信息
    int CountObjects() const;//快递个数
};

