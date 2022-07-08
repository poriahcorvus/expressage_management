#include "Manager.h"
#include "Objects.h"
#include "Users.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
using namespace std;


Manager::Manager() {
    this->m_username = "";
    this->m_name = "";
    this->m_password = "";
    this->m_remaining = 0;
}

Manager::~Manager() {}

int Manager::LogIn2() {
    string username;
    string password;

    cout << "\n用户名：";
    cin >> username;
    cout << "密码：";
    cin >> password;

    string t_username;//用户名
    string t_name;//姓名
    string t_password;//密码
    double t_remaining;//账户余额

    ifstream fl;
    fl.open("manager.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取管理员信息失败" << endl;
        return -1;
    }

    fl >> t_username;
    fl >> t_name;
    fl >> t_password;
    fl >> t_remaining;

    fl.close();

    if (username == t_username && password == t_password) {
        this->m_username = username;
        this->m_name = t_name;
        this->m_password = password;
        this->m_remaining = t_remaining;
        cout << "\n登陆成功！\n管理员您好！" << endl;
        return 1;
    }
    else {
        cout << "\n请输入正确的用户名和密码！\n" << endl;
        return 0;
    }
}

void Manager::UsInfo() const {
    cout << "\n您正在查看所有用户信息！\n" << endl;
    ifstream fl;
    fl.open("users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "查看用户信息失败！" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";//密码不显示
    double t5 = 0;
    string t6 = "";
    Users user;
    int number = user.Count();
    cout << "用户数：" << number << '\n' << endl;
    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;

        cout << "用户名：" << t1
            << "\n姓名：" << t2
            << "\n联系方式：" << t3
            << "\n账户余额：" << t5
            << "\n地址：" << t6
            << '\n' << endl;

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";//密码不显示
        t5 = 0;
        t6 = "";
    }
    fl.close();
}

void Manager::ObInfo() const {
    cout << "\n您正在查看所有快递信息！\n" << endl;
    ifstream fl;
    fl.open("objects.txt", ios::in);
    if (!fl.is_open()) {
        cout << "查看快递信息失败！" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    int t4 = -1;
    string t5 = "";
    string t6 = "";
    string t7 = "";
    Objects obj;
    int number = obj.CountObjects();
    cout << "共有快递数：" << number << '\n' << endl;
    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;
        fl >> t7;

        cout << "\n快递单号：" << t1
            << "\n收件人：" << t2
            << "\n寄件人：" << t3
            << "\n快递描述：" << t7;
        if (t4 == 1) {
            cout << "\n快递正在派送中" << endl;
        }
        else if (t4 == 0) {
            cout << "\n快递已送达" << endl;
        }

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = -1;
        t5 = "";
        t6 = "";
        t7 = "";
    }
    fl.close();
}

void Manager::SearchInfo() const {
    cout << "\n请选择您要查询的内容：" << endl;
    cout << "1 - 用户\n2 - 查询快递单号\n3 - 查询发送时间\n4 - 查询签收时间\n0 - 退出查询" << endl;
    int op;
    cin >> op;
    switch (op) {
    case 1:     SearchUser();       break;
    case 2:     SearchNumber();     break;
    case 3:     SearchTime_1();     break;
    case 4:     SearchTime_2();     break;
    case 0:     break;
    default:    cout << "\n请输入合法的操作！" << endl;
    }
    while (op) {
        cout << "\n请选择您要查询的内容：" << endl;
        cout << "1 - 用户\n2 - 查询快递单号\n3 - 查询发送时间\n4 - 查询签收时间\n0 - 退出查询" << endl;
        cin >> op;
        switch (op) {
        case 1:     SearchUser();       break;
        case 2:     SearchNumber();     break;
        case 3:     SearchTime_1();     break;
        case 4:     SearchTime_2();     break;
        case 0:     break;
        default:    cout << "\n请输入合法的操作！" << endl;
        }
    }
}

void Manager::SearchUser() const {
    cout << "\n请输入您要查询的用户名：";
    Users user;
    cin >> user.m_username;

    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额
    vector<string> t_address;//地址

    user.Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);
    int number = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (user.m_username == t_username[i]) {
            number = i;
            break;
        }
    }

    if (number == -1) {
        cout << "\n该用户不存在！" << endl;
        return;
    }

    cout << "\n用户名：" << t_username[number]
        << "\n姓名：" << t_name[number]
        << "\n联系方式：" << t_phone[number]
        << "\n账户余额：" << t_remaining[number]
        << "\n地址：" << t_address[number]
        << '\n' << endl;

    Objects obj;
    cout << "\n该用户寄出的包裹：" << endl;
    obj.MyExpress(user.m_username);
    cout << "\n该用户收到的包裹：" << endl;
    obj.MyReceive(user.m_username);

}

void Manager::SearchNumber() const {
    Objects obj;
    string number;
    cout << "\n请输入所要查询的快递单号：";
    cin >> number;

    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_number[i] == number) {
            isin = 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n快递状态：已签收";
            else if (t_state[i] == 1)
                cout << "\n快递状态：派送中";
            cout << "\n发出时间：" << t_time1[i]
                << "\n签收时间：" << t_time2[i]
                << "\n备注：" << t_description[i]
                << endl;
            break;
        }
    }

    if (isin == 0)
        cout << "\n快递不存在！\n" << endl;
}

void Manager::SearchTime_1() const {
    Objects obj;
    string time1;
    cout << "\n请输入所要查询的快递发送时间：";
    cin >> time1;

    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_time1[i] == time1) {
            isin = 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n快递状态：已签收";
            else if (t_state[i] == 1)
                cout << "\n快递状态：派送中";
            cout << "\n发出时间：" << t_time1[i]
                << "\n签收时间：" << t_time2[i]
                << "\n备注：" << t_description[i]
                << endl;
        }
    }

    if (isin == 0)
        cout << "\n无历史记录！\n" << endl;

}

void Manager::SearchTime_2() const {
    Objects obj;
    string time2;
    cout << "\n请输入所要查询的快递签收时间：";
    cin >> time2;

    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_time2[i] == time2) {
            isin = 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n快递状态：已签收";
            else if (t_state[i] == 1)
                cout << "\n快递状态：派送中";
            cout << "\n发出时间：" << t_time1[i]
                << "\n签收时间：" << t_time2[i]
                << "\n备注：" << t_description[i]
                << endl;
        }
    }

    if (isin == 0)
        cout << "\n无历史记录！\n" << endl;

}

/*
void Manager::RemainAdd(){
    this->m_remaining += 15;
}
*/

void Manager::UpdateRemain() const {
    ifstream fl;
    fl.open("manager.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取管理员信息失败" << endl;
        return;
    }
    string t_username;
    string t_name;
    string t_password;
    double t_remaining;

    fl >> t_username;
    fl >> t_name;
    fl >> t_password;
    fl >> t_remaining;

    t_remaining += 15;

    ofstream change;
    change.open("manager.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("manager.txt", ios::app);
    if (!write.is_open()) {
        cout << "管理员信息更新失败！" << endl;
        return;
    }
    write << t_username << ' ' << t_name << ' ' << t_password << ' ' << t_remaining << endl;
    write.close();
}

/*
void Manager::SignUpMess(){
    string username;
    string name;
    string password;
    double remaining;

    cout << "用户名：";
    cin >> username;
    cout << "姓名：";
    cin >> name;
    cout << "密码：";
    cin >> password;
    cout << "收入：";
    cin >> remaining;

    fstream write;
    write.open("manager.txt", ios::out | ios::app);
    if(!write.is_open()){
        cout << "管理员信息设置失败！" << endl;
        return;
    }
    write << username << ' ' << name << ' ' << password << ' ' << remaining << endl;
    write.close();
}
*/
/*
int Manager::UserSum(){
    ifstream fl;
    fl.open("users.txt", ios::in);
    if(!fl.is_open()){
        cout << "读取用户数失败" << endl;
        return -1;
    }

    int count = 0;
    char temp[1024];
    while(!fl.eof()){
        fl.getline(temp, 1024);
        count ++;
    }
    fl.close();
    count --;
    return count;
}

int Manager::ObjSum(){
    ifstream fl;
    fl.open("objects.txt", ios::in);
    if(!fl.is_open()){
        cout << "读取快递数失败" << endl;
        return -1;
    }

    int count = 0;
    char temp[1024];
    while(!fl.eof()){
        fl.getline(temp, 1024);
        count ++;
    }
    fl.close();
    count --;
    return count;
}
*/