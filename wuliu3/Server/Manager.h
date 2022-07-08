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
    void UsInfo(SOCKET recvsockCli) const;//查看所有用户信息
    void ObInfo(SOCKET recvsockCli) const;//查看所有快递信息
    void CoInfo(SOCKET recvsockCli) const;//查看所有快递员信息
    void SearchInfo(SOCKET recvsockCli) const;//查询
    void SearchUser(SOCKET recvsockCli) const;//查询用户
    void SearchExpress(SOCKET recvsockCli) const;//查询寄件人
    void SearchReceive(SOCKET recvsockCli) const;//查询发件人
    void SearchT1(SOCKET recvsockCli) const;//查询寄件时间
    void SearchT2(SOCKET recvsockCli) const;//查询收件时间
    void SearchCourier(SOCKET recvsockCli) const;//查询快递员
    void SearchNum(SOCKET recvsockCli) const;//查询快递单号
    //void SearchNumber();//查询快递单号
    //void SearchTime_1();//查询发送时间
    //void SearchTime_2();//查询签收时间
    //void RemainAdd();//收入
    void UpdateRemain(double price, SOCKET recvsockCli) const;//更新余额
    //void SignUpMess();//设置管理员信息
    //int UserSum();//用户总数
    //int ObjSum();//快递总数
    void ManageCour(SOCKET recvsockCli) const;//管理快递员
    void AllotCour(SOCKET recvsockCli) const;//为快递分配快递员
};

