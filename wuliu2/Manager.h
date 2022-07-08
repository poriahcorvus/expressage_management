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
    void UsInfo() const;//查看所有用户信息
    void ObInfo() const;//查看所有快递信息
    void CoInfo() const;//查看所有快递员信息
    void SearchInfo() const;//查询
    void SearchUser() const;//查询用户
    void SearchExpress() const;//查询寄件人
    void SearchReceive() const;//查询发件人
    void SearchT1() const;//查询寄件时间
    void SearchT2() const;//查询收件时间
    void SearchCourier() const;//查询快递员
    void SearchNum() const;//查询快递单号
    //void SearchNumber();//查询快递单号
    //void SearchTime_1();//查询发送时间
    //void SearchTime_2();//查询签收时间
    //void RemainAdd();//收入
    void UpdateRemain(double price) const;//更新余额
    //void SignUpMess();//设置管理员信息
    //int UserSum();//用户总数
    //int ObjSum();//快递总数
    void ManageCour() const;//管理快递员
    void AllotCour() const;//分配快递员
};

