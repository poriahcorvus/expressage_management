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
    void UsInfo() const;//查看所有用户信息
    void ObInfo() const;//查看所有快递信息
    void SearchInfo() const;//查询
    void SearchUser() const;//查询用户
    void SearchNumber() const;//查询快递单号
    void SearchTime_1() const;//查询发送时间
    void SearchTime_2() const;//查询签收时间
    //void RemainAdd();//收入
    void UpdateRemain() const;//更新
    //void SignUpMess();//设置管理员信息
    //int UserSum();//用户总数
    //int ObjSum();//快递总数
};

