#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
using namespace std;

class Users
{
    friend class Manager;
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
    int LogIn1();//登录
    void SignUp();//注册
    void SetMess();//设置信息
    void ChangePass();//更改密码
    void CheckRemain() const;//查询账户余额
    void TopUp();//账户充值
    void ExpressDel();//寄快递
    void ReceiveDel() const;//收快递
    void SearchDel() const;//查询快递
    int Count() const;//查询已注册用户数
    void Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<double>& t_remaining, vector<string>& t_address) const;//文件中的用户信息
    void SaveInfo() const;//保存信息
    void UpdateInfo() const;//更新信息
};

