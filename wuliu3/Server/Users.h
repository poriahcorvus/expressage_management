#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
#include "Objects.h"
using namespace std;

class Users
{
private:
    string m_username;//用户名
    string m_name;//姓名
    string m_phone;//电话
    string m_password;//密码
    double m_remaining;//账户余额
    string m_address;//地址

public:
    Users();
    ~Users();
    int LogIn1(SOCKET recvsockCli);//登录
    void SignUp(SOCKET recvsockCli);//注册
    void SetMess(SOCKET recvsockCli);//设置信息
    void ChangePass(SOCKET recvsockCli);//更改密码
    void CheckRemain(SOCKET recvsockCli) const;//查询账户余额
    void TopUp(SOCKET recvsockCli);//账户充值
    void ExpressDel(SOCKET recvsockCli);//寄快递
    void Express(Objects& ob, SOCKET recvsockCli);
    void ReceiveDel(SOCKET recvsockCli) const;//收快递
    void SearchDel(SOCKET recvsockCli) const;//查询快递
    int Count() const;//查询已注册用户数
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<string>& t_remaining, vector<string>& t_address) const;//文件中的用户信息
    void SaveInfo(SOCKET recvsockCli) const;//保存信息
    void UpdateInfo() const;//更新信息
};

