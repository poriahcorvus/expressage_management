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
    string m_username;//用户名
    string m_name;//姓名
    string m_phone;
    string m_password;//密码
    double m_remaining;//余额

public:
    Courier();
    ~Courier();
    int LogIn3();//登录
    void SetCourier();//设置快递员
    void RemoveCourier() const;//删除快递员
    void SendDel();//揽收快递
    void SearchDel() const;//查询快递
    void SearchS0() const;//查询已送达
    void SearchS1() const;//查询已揽收
    void SearchUser1() const;//查询寄件人
    void SearchUser2() const;//查询收件人
    void SearchT1() const;//查询寄件时间
    void SearchT2() const;//查询收件时间
    void SearchNum() const;//查询单号
    int Count() const;//查询快递员数目
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<double>& t_remaining) const;//文件中的快递员信息
    void SaveInfo() const;//保存信息
    void UpdateInfo() const;//更新信息
};

