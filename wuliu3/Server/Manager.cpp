#include "Manager.h"
#include "Courier.h"
#include "Users.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"
#include "public.h"

Manager::Manager() {
    this->m_username = "";
    this->m_name = "";
    this->m_password = "";
    this->m_remaining = 0;
}

Manager::~Manager() {}

int Manager::LogIn2(SOCKET recvsockCli) {
    string username;
    string password;

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n用户名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    username = recvBuf;
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n密码：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    password = recvBuf;
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    string t_username;//用户名
    string t_name;//姓名
    string t_password;//密码
    double t_remaining;//账户余额

    ifstream fl;
    fl.open("./data/manager.txt", ios::in);
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
        strcpy(sendBuf, "\n登陆成功！\n管理员您好！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf << endl;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return 1;
    }
    else {
        strcpy(sendBuf, "\n请输入正确的用户名和密码！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf << endl;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return 0;
    }
}

void Manager::UsInfo(SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n您正在查看所有用户信息！\n");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    ifstream fl;
    fl.open("./data/users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "查看用户信息失败！" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";//密码不显示
    string t5 = "";
    string t6 = "";
    Users user;
    int number = user.Count();

    string its = to_string(number);
    strcpy(sendBuf, "\n用户数：");
    strcat(sendBuf, (char*)its.c_str());
    strcat(sendBuf, "\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;

        strcpy(sendBuf, "\n用户名：");
        strcat(sendBuf, (char*)t1.c_str());
        strcat(sendBuf, "\n姓名：");
        strcat(sendBuf, (char*)t2.c_str());
        strcat(sendBuf, "\n联系方式：");
        strcat(sendBuf, (char*)t3.c_str());
        strcat(sendBuf, "\n账户余额：");
        strcat(sendBuf, (char*)t5.c_str());
        strcat(sendBuf, "\n地址：");
        strcat(sendBuf, (char*)t6.c_str());
        strcat(sendBuf, "\n\n");

        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";//密码不显示
        t5 = "";
        t6 = "";
    }
    fl.close();
}

void Manager::ObInfo(SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n您正在查看所有快递信息！\n");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    ifstream fl;
    fl.open("./data/objects.txt", ios::in);
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
    int t8 = -1;
    string t9 = "";
    string t10 = "";

    Objects obj;
    int number = obj.CountObjects();

    string its = to_string(number);
    strcpy(sendBuf, "\n快递数：");
    strcat(sendBuf, (char*)its.c_str());
    strcat(sendBuf, "\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf << endl;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;
        fl >> t7;
        fl >> t8;
        fl >> t9;
        fl >> t10;

        strcpy(sendBuf, "\n快递单号：");
        strcat(sendBuf, (char*)t1.c_str());
        strcat(sendBuf, "\n寄件人：");
        strcat(sendBuf, (char*)t2.c_str());
        strcat(sendBuf, "\n收件人：");
        strcat(sendBuf, (char*)t3.c_str());
        strcat(sendBuf, "\n快递状态：");
        if (t4 == 0)
            strcat(sendBuf, "已签收");
        else if (t4 == 1)
            strcat(sendBuf, "待签收");
        else if (t4 == 2)
            strcat(sendBuf, "待揽收");
        strcat(sendBuf, "\n寄件时间");
        strcat(sendBuf, (char*)t5.c_str());
        strcat(sendBuf, "\n收件时间");
        strcat(sendBuf, (char*)t6.c_str());
        strcat(sendBuf, "\n快递员：");
        strcat(sendBuf, (char*)t7.c_str());
        strcat(sendBuf, "\n物品分类：");
        if (t8 == 1)
            strcat(sendBuf, "易碎品");
        else if (t8 == 2)
            strcat(sendBuf, "图书");
        else if (t8 == 3)
            strcat(sendBuf, "普通快递");
        strcat(sendBuf, "\n快递重量：");
        strcat(sendBuf, (char*)t9.c_str());
        strcat(sendBuf, "\n备注：");
        strcat(sendBuf, (char*)t10.c_str());
        strcat(sendBuf, "\n");

        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = -1;
        t5 = "";
        t6 = "";
        t7 = "";
        t8 = -1;
        t9 = "";
        t10 = "";
    }
    fl.close();
}

void Manager::CoInfo(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n您正在查看所有快递员信息！\n");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    ifstream fl;
    fl.open("./data/couriers.txt", ios::in);
    if (!fl.is_open()) {
        cout << "查看快递员信息失败！" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";//密码不显示
    string t5 = "";
    Courier courier;
    int number = courier.Count();

    string its = to_string(number);
    strcpy(sendBuf, "\n快递员数：");
    strcat(sendBuf, (char*)its.c_str());
    strcat(sendBuf, "\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf << endl;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;

        strcpy(sendBuf, "\n用户名：");
        strcat(sendBuf, (char*)t1.c_str());
        strcat(sendBuf, "\n姓名：");
        strcat(sendBuf, (char*)t2.c_str());
        strcat(sendBuf, "\n联系方式：");
        strcat(sendBuf, (char*)t3.c_str());
        strcat(sendBuf, "\n账户余额：");
        strcat(sendBuf, (char*)t5.c_str());
        strcat(sendBuf, "\n");

        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";//密码不显示
        t5 = "";
    }
    fl.close();
}

void Manager::SearchInfo(SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请选择您要查询的内容：\n\n1 - 所有用户\n2 - 所有快递\n3 - 所有快递员\n\n4 - 普通用户\n5 - 寄件人\n6 - 收件人\n7 - 寄件时间\n8 - 收件时间\n9 - 快递员\n10 - 快递单号\n0 - 退出\n");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;
    string cts = recvBuf;

    int op = atoi(cts.c_str());
    Objects ob;
    while (op) {

        if (op == 1)
            UsInfo(recvsockCli);
        else if (op == 2)
            ObInfo(recvsockCli);
        else if (op == 3)
            CoInfo(recvsockCli);
        else if (op == 4)
            SearchUser(recvsockCli);
        else if (op == 5)
            SearchExpress(recvsockCli);
        else if (op == 6)
            SearchReceive(recvsockCli);
        else if (op == 7)
            SearchT1(recvsockCli);
        else if (op == 8)
            SearchT2(recvsockCli);
        else if (op == 9)
            SearchCourier(recvsockCli);
        else if (op == 10)
            SearchNum(recvsockCli);
        else {
            strcpy(sendBuf, "\n请输入合法的操作选项！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }

        strcpy(sendBuf, "\n请选择您要查询的内容：\n\n1 - 所有用户\n2 - 所有快递\n3 - 所有快递员\n\n4 - 普通用户\n5 - 寄件人\n6 - 收件人\n7 - 寄件时间\n8 - 收件时间\n9 - 快递员\n10 - 快递单号\n0 - 退出\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        cout << recvBuf;
        reLen = SOCKET_ERROR;
        cts = recvBuf;
        op = atoi(cts.c_str());
    }
}

void Manager::SearchUser(SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入您要查询的用户名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    Users user;
    string username = recvBuf;

    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<string> t_remaining;//账户余额
    vector<string> t_address;//地址

    user.Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);
    int number = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (username == t_username[i]) {
            number = i;
            break;
        }
    }

    if (number == -1) {
        strcpy(sendBuf, "\n该用户不存在！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }

    strcpy(sendBuf, "\n用户名：");
    strcat(sendBuf, (char*)t_username[number].c_str());
    strcat(sendBuf, "\n姓名：");
    strcat(sendBuf, (char*)t_name[number].c_str());
    strcat(sendBuf, "\n联系方式：");
    strcat(sendBuf, (char*)t_phone[number].c_str());
    strcat(sendBuf, "\n账户余额：");
    strcat(sendBuf, (char*)t_remaining[number].c_str());
    strcat(sendBuf, "\n地址：");
    strcat(sendBuf, (char*)t_address[number].c_str());
    strcat(sendBuf, "\n");

    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    Objects obj;
    strcpy(sendBuf, "\n该用户寄出的包裹：\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    obj.MyExpress(username, recvsockCli);

    strcpy(sendBuf, "\n该用户收到的包裹：\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    obj.MyReceive(username, recvsockCli);


}

void Manager::SearchExpress(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入您要查询的寄件人用户名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    string username = recvBuf;

    Objects ob;
    ob.MyExpress(username, recvsockCli);
}

void Manager::SearchReceive(SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入您要查询的收件人用户名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    string username = recvBuf;

    Objects ob;
    ob.MyReceive(username, recvsockCli);
}

void Manager::SearchT1(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchTime1(this->m_username, 1, recvsockCli);
}
void Manager::SearchT2(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchTime2(this->m_username, 1, recvsockCli);
}

void Manager::SearchCourier(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入您要查询的快递员用户名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    string username = recvBuf;

    Courier courier;
    Objects ob;
    int index = 0;
    int isin = 0;
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<string> t_remaining;//账户余额
    courier.Info(t_username, t_name, t_phone, t_password, t_remaining);
    for (int i = 0; i < t_username.size(); i++) {
        if (t_username[i] == username) {
            isin = 1;
            index = i;
            break;
        }
    }
    if (isin == 0) {
        strcpy(sendBuf, "\n请输入正确的快递员用户名！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;
        return;
    }

    strcpy(sendBuf, "\n用户名：");
    strcat(sendBuf, (char*)t_username[index].c_str());
    strcat(sendBuf, "\n姓名：");
    strcat(sendBuf, (char*)t_name[index].c_str());
    strcat(sendBuf, "\n联系方式：");
    strcat(sendBuf, (char*)t_phone[index].c_str());
    strcat(sendBuf, "\n账户余额：");
    strcat(sendBuf, (char*)t_remaining[index].c_str());
    strcat(sendBuf, "\n");

    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n该快递员已揽收的快递：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    ob.SearchState1(username, recvsockCli);


    strcpy(sendBuf, "\n该快递员已派送的快递：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    ob.SearchState0(username, recvsockCli);

}

void Manager::SearchNum(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchNumber(this->m_username, 1, recvsockCli);
}

/*
void Manager::SearchNumber(){
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
    vector<string> t_cour;
    vector<int> t_type;
    vector<double> t_weight;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;

    for(int i = 0; i < t_number.size(); i ++){
        if(t_number[i] == number){
            isin = 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i];
            if(t_state[i] == 0)
                cout << "\n快递状态：已签收";
            else if(t_state[i] == 1)
                cout << "\n快递状态：派送中";
            cout << "\n发出时间：" << t_time1[i]
                << "\n签收时间：" << t_time2[i]
                << "\n备注：" << t_description[i]
                << endl;
            break;
        }
    }

    if(isin == 0)
        cout << "\n快递不存在！\n" << endl;
}

void Manager::SearchTime_1(){
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
    vector<string> t_cour;
    vector<int> t_type;
    vector<double> t_weight;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;

    for(int i = 0; i < t_number.size(); i ++){
        if(t_time1[i] == time1){
            isin = 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i];
            if(t_state[i] == 0)
                cout << "\n快递状态：已签收";
            else if(t_state[i] == 1)
                cout << "\n快递状态：派送中";
            cout << "\n发出时间：" << t_time1[i]
                << "\n签收时间：" << t_time2[i]
                << "\n备注：" << t_description[i]
                << endl;
        }
    }

    if(isin == 0)
        cout << "\n无历史记录！\n" << endl;

}

void Manager::SearchTime_2(){
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
    vector<string> t_cour;
    vector<int> t_type;
    vector<double> t_weight;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;

    for(int i = 0; i < t_number.size(); i ++){
        if(t_time2[i] == time2){
            isin = 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i];
            if(t_state[i] == 0)
                cout << "\n快递状态：已签收";
            else if(t_state[i] == 1)
                cout << "\n快递状态：派送中";
            cout << "\n发出时间：" << t_time1[i]
                << "\n签收时间：" << t_time2[i]
                << "\n备注：" << t_description[i]
                << endl;
        }
    }

    if(isin == 0)
        cout << "\n无历史记录！\n" << endl;

}
*/
/*
void Manager::RemainAdd(){
    this->m_remaining += 15;
}
*/

void Manager::UpdateRemain(double price, SOCKET recvsockCli) const {
    ifstream fl;
    fl.open("./data/manager.txt", ios::in);
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

    t_remaining = t_remaining + price;

    ofstream change;
    change.open("./data/manager.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("./data/manager.txt", ios::app);
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

void Manager::ManageCour(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请选择：\n1 - 添加快递员\n2 - 删除快递员\n0 - 退出管理\n");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    int choice = atoi(recvBuf);

    while (choice) {
        Courier courier;
        if (choice == 1)
            courier.SetCourier(recvsockCli);
        else if (choice == 2)
            courier.RemoveCourier(recvsockCli);

        strcpy(sendBuf, "\n请选择：\n1 - 添加快递员\n2 - 删除快递员\n0 - 退出管理\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        cout << recvBuf << endl;
        reLen = SOCKET_ERROR;
        choice = atoi(recvBuf);
    }
}

void Manager::AllotCour(SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n您正在指派快递员\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_cour;
    vector<int> t_type;
    vector<string> t_weight;
    vector<string> t_description;

    Objects obj;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);
    int isex = 0;
    for (int i = 0; i < t_number.size(); i++) {
        if (t_state[i] == 2 && t_cour[i] == "暂无") {
            isex += 1;
            strcpy(sendBuf, "\n快递单号：");
            strcat(sendBuf, (char*)t_number[i].c_str());
            strcat(sendBuf, "\n寄件人：");
            strcat(sendBuf, (char*)t_user1[i].c_str());
            strcat(sendBuf, "\n收件人：");
            strcat(sendBuf, (char*)t_user2[i].c_str());
            strcat(sendBuf, "\n物品分类：");
            if (t_type[i] == 1)
                strcat(sendBuf, "易碎品");
            else if (t_type[i] == 2)
                strcat(sendBuf, "图书");
            else if (t_type[i] == 3)
                strcat(sendBuf, "普通快递");
            strcat(sendBuf, "\n快递重量：");
            strcat(sendBuf, (char*)t_weight[i].c_str());
            strcat(sendBuf, "\n备注：");
            strcat(sendBuf, (char*)t_description[i].c_str());
            strcat(sendBuf, "\n");

            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

        }
    }
    if (isex == 0) {
        strcpy(sendBuf, "\n所有快递都已指派快递员！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }

    strcpy(sendBuf, "\n请输入要指派快递员的快递单号：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string se = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    int isin = 0;
    string co = "";

    for (int i = 0; i < t_number.size(); i++) {
        if (t_number[i] == se) {
            isin = 1;
            isex -= 1;

            Objects ob;
            ob.m_number = se;

            strcpy(sendBuf, "\n请输入快递员用户名：");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "1");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
            co = recvBuf;
            cout << recvBuf;
            reLen = SOCKET_ERROR;
            ob.m_cour = co;
            ob.m_state = t_state[i];
            ob.m_time2 = t_time2[i];
            ob.UpdateObjects();

            strcpy(sendBuf, "\n指派成功！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            break;
        }
    }

    if (isin == 0) {
        strcpy(sendBuf, "\n请输入正确的快递单号！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }

    if (isex == 0) {
        strcpy(sendBuf, "\n所有快递都已指派快递员！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
        return;
    }

    strcpy(sendBuf, "\n是否继续指派快递员？\n1 - 继续\t0 - 退出\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    int iscon = atoi(recvBuf);
    reLen = SOCKET_ERROR;

    while (iscon == 1) {
        se = "";
        co = "";
        isin = 0;

        strcpy(sendBuf, "\n请输入要指派快递员的快递单号：");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        string se = recvBuf;
        cout << recvBuf;
        reLen = SOCKET_ERROR;

        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == se) {
                isin = 1;
                isex -= 1;

                Objects ob;
                ob.m_number = se;

                strcpy(sendBuf, "\n请输入快递员用户名：");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "1");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
                co = recvBuf;
                cout << recvBuf;
                reLen = SOCKET_ERROR;
                ob.m_cour = co;
                ob.m_state = t_state[i];
                ob.m_time2 = t_time2[i];
                ob.UpdateObjects();

                strcpy(sendBuf, "\n指派成功！\n");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "0");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                break;
            }
        }

        if (isin == 0) {
            strcpy(sendBuf, "\n请输入正确的快递单号！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }

        if (isex == 0) {
            strcpy(sendBuf, "\n所有快递都已指派快递员！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
            return;
        }

        strcpy(sendBuf, "\n是否继续指派快递员？\n1 - 继续\t0 - 退出\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        cout << recvBuf;
        iscon = atoi(recvBuf);
        reLen = SOCKET_ERROR;

    }




}