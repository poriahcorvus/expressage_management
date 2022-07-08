#include "Users.h"
#include "Manager.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"
#include "public.h"

Users::Users() {
    this->m_username = "";
    this->m_name = "";
    this->m_phone = "";
    this->m_password = "";
    this->m_remaining = 0;
    this->m_address = "";
}
Users::~Users() {}

int Users::LogIn1(SOCKET recvsockCli) {

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
    string username = recvBuf;
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
    string password = recvBuf;
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<string> t_remaining;//账户余额
    vector<string> t_address;//地址

    Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);

    int us_flag = 0;
    int pas_flag = 0;
    int i;
    for (i = 0; i < Count(); i++) {
        if (username == t_username[i] && password == t_password[i]) {
            us_flag = 1;
            pas_flag = 1;
            break;
        }
    }

    if (us_flag == 1 && pas_flag == 1) {
        this->m_username = t_username[i];
        this->m_name = t_name[i];
        this->m_phone = t_phone[i];
        this->m_password = t_password[i];
        this->m_remaining = stod(t_remaining[i]);
        this->m_address = t_address[i];

        strcpy(sendBuf, "\n登陆成功！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return 1;
    }
    else {
        strcpy(sendBuf, "\n请输入正确的用户名和密码！");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return 0;
    }
}

void Users::SignUp(SOCKET recvsockCli) {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请设置一个用户名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string username = recvBuf;
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    int num = Count();
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<string> t_remaining;//账户余额
    vector<string> t_address;//地址
    Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);

    int us_flag = 0;
    for (int i = 0; i < num; i++) {
        if (username == t_username[i]) {
            us_flag = 1;
            break;
        }
    }
    while (us_flag) {
        strcpy(sendBuf, "\n用户名已存在！\n请设置一个用户名：");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        username = recvBuf;
        cout << recvBuf;
        reLen = SOCKET_ERROR;

        us_flag = 0;
        for (int i = 0; i < num; i++) {
            if (username == t_username[i]) {
                us_flag = 1;
                break;
            }
        }
    }

    strcpy(sendBuf, "\n请设置密码：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string password1 = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n请确认密码：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string password2 = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    while (password1 != password2) {
        strcpy(sendBuf, "\n两次密码不一致\n请重新确认密码：");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        password2 = recvBuf;
        cout << recvBuf;
        reLen = SOCKET_ERROR;
    }

    this->m_username = username;
    this->m_password = password1;

    strcpy(sendBuf, "\n注册成功！\n请完善您的个人信息！");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    SetMess(recvsockCli);
    SaveInfo(recvsockCli);

    strcpy(sendBuf, "\n请重新登录以验证身份！\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;
}

void Users::SetMess(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n您的姓名：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string name = recvBuf;
    cout << recvBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n您的手机号：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string phone = recvBuf;
    cout << recvBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n您的地址：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string address = recvBuf;
    cout << recvBuf;
    sLen = SOCKET_ERROR;

    this->m_name = name;
    this->m_phone = phone;
    this->m_address = address;
}

void Users::ChangePass(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n您正在修改密码！\n请输入新密码：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    string new_password = recvBuf;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n请确认新密码：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    string n_password = recvBuf;
    reLen = SOCKET_ERROR;

    while (new_password != n_password) {
        strcpy(sendBuf, "\n两次密码不一致\n请重新确认密码：");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        cout << recvBuf;
        n_password = recvBuf;
        reLen = SOCKET_ERROR;
    }

    strcpy(sendBuf, "\n密码修改成功！\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    this->m_password = new_password;
    UpdateInfo();
}

void Users::CheckRemain(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n您正在查询账户余额!\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    stringstream ss;
    ss << this->m_remaining;
    string s = ss.str();
    strcpy(sendBuf, "您的账户余额为：");
    strcat(sendBuf, (char*)s.c_str());
    strcat(sendBuf, "\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;
}

void Users::TopUp(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n请输入您要充值的金额（整数）：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    int add = atoi(recvBuf);
    reLen = SOCKET_ERROR;

    this->m_remaining += add;

    strcpy(sendBuf, "\n充值成功！\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    stringstream ss;
    ss << this->m_remaining;
    string s = ss.str();
    strcpy(sendBuf, "\n您的账户余额为：");
    strcat(sendBuf, (char*)s.c_str());
    strcat(sendBuf, "\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    UpdateInfo();
}

void Users::ExpressDel(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n您正在申请发送快递\n\n请选择快递物品分类：\n1 - 易碎品\t2 - 图书\t3 - 普通物品\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    int tp = atoi(recvBuf);
    reLen = SOCKET_ERROR;

    if (tp == 1) {
        Fragile ob;
        Express(ob, recvsockCli);
        double price = ob.GetPrice(ob.m_weight);

        if (this->m_remaining >= price) {
            ob.SaveObjects();
            strcpy(sendBuf, "\n快递已打包，正在等待揽收！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price, recvsockCli);
        }
        else {
            strcpy(sendBuf, "\n余额不足，请充值！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (tp == 2) {
        Book ob;
        Express(ob, recvsockCli);
        double price = ob.GetPrice(ob.m_weight);

        if (this->m_remaining >= price) {
            ob.SaveObjects();
            strcpy(sendBuf, "\n快递已打包，正在等待揽收！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price, recvsockCli);
        }
        else {
            strcpy(sendBuf, "\n余额不足，请充值！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }

    else if (tp == 3) {
        Ordinary ob;
        Express(ob, recvsockCli);
        double price = ob.GetPrice(ob.m_weight);

        if (this->m_remaining >= price) {
            ob.SaveObjects();
            strcpy(sendBuf, "\n快递已打包，正在等待揽收！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price, recvsockCli);
        }
        else {
            strcpy(sendBuf, "\n余额不足，请充值！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
}

void Users::Express(Objects& ob, SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    ob.m_number = ob.GetNum();
    ob.m_user1 = this->m_username;

    strcpy(sendBuf, "\n请输入收件人用户名：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    ob.m_user2 = recvBuf;
    ob.m_state = 2;//0-已签收，1-待签收， 2-待揽收
    ob.m_time1 = ob.GetTime();
    ob.m_time2 = "暂无";
    ob.m_cour = "暂无";

    strcpy(sendBuf, "\n请输入快递重量：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    ob.m_weight = stod(recvBuf);
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n请输入快递备注：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;
    ob.m_description = recvBuf;
 
}

void Users::ReceiveDel(SOCKET recvsockCli )const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n您正在签收快递！\n");
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

    Objects ob;
    ob.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);
    int isex = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_user2[i] == this->m_username && t_state[i] == 1) {
            isex += 1;
            strcpy(sendBuf, "\n快递单号：");
            strcat(sendBuf, t_number[i].c_str());
            strcat(sendBuf, "\n寄件人：");
            strcat(sendBuf, t_user1[i].c_str());
            strcat(sendBuf, "\n物品类别：");
            if (t_type[i] == 1)
                strcat(sendBuf, "易碎品");
            else if (t_type[i] == 2)
                strcat(sendBuf, "图书");
            else if (t_type[i] == 3)
                strcat(sendBuf, "普通物品");
            strcat(sendBuf, "\n备注：");
            strcat(sendBuf, t_description[i].c_str());
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
        strcpy(sendBuf, "\n您没有待签收的快递！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }

    strcpy(sendBuf, "\n请选择要签收的快递（输入单号）：");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;
    string acc = recvBuf;
    string tm = ob.GetTime();

    for (int i = 0; i < t_number.size(); i++) {
        if (t_user2[i] == this->m_username && t_state[i] == 1 && t_number[i] == acc) {
            t_state[i] = 0;
            t_time2[i] = tm;

            ob.m_number = acc;
            ob.m_state = 0;
            ob.m_time2 = tm;
            ob.m_cour = t_cour[i];
            ob.UpdateObjects();

            isex -= 1;

            strcpy(sendBuf, "\n签收成功！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
            break;
        }
    }

    if (isex > 0) {
        strcpy(sendBuf, "\n是否继续签收快递？\n1 - 继续签收快递\t0 - 退出\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        cout << recvBuf;
        reLen = SOCKET_ERROR;
        int iscon = atoi(recvBuf);

        while (iscon == 1) {
            acc = "";
            tm = "";

            strcpy(sendBuf, "\n请选择要签收的快递（输入单号）：");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "1");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
            cout << recvBuf;
            reLen = SOCKET_ERROR;
            acc = recvBuf;
            tm = ob.GetTime();

            for (int i = 0; i < t_number.size(); i++) {
                if (t_user2[i] == this->m_username && t_state[i] == 1 && t_number[i] == acc) {
                    t_state[i] = 0;
                    t_time2[i] = tm;

                    ob.m_number = acc;
                    ob.m_state = 0;
                    ob.m_time2 = tm;
                    ob.UpdateObjects();

                    isex -= 1;

                    strcpy(sendBuf, "\n签收成功！\n");
                    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                    cout << sendBuf;
                    sLen = SOCKET_ERROR;

                    strcpy(sendBuf, "0");
                    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                    sLen = SOCKET_ERROR;

                    break;
                }
            }

            if (isex > 0) {
                strcpy(sendBuf, "\n是否继续签收快递？\n1 - 继续签收快递\t0 - 退出\n");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "1");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
                cout << recvBuf;
                iscon = atoi(recvBuf);
            }
            else {
                strcpy(sendBuf, "\n您没有待签收的快递！\n");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "0");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                return;
            }
        }
    }
    else {
        strcpy(sendBuf, "\n您没有待签收的快递！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }
}

void Users::SearchDel(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n请选择您要查询的内容：\n1 - 我寄出的\n2 - 我收到的\n3 - 查询快递单号\n4 - 查询发送时间\n5 - 查询签收时间\n0 - 退出查询\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;
    int op = atoi(recvBuf);
    Objects obj;
    while (op) {

        if (op == 1)
            obj.MyExpress(this->m_username, recvsockCli);
        else if (op == 2)
            obj.MyReceive(this->m_username, recvsockCli);
        else if (op == 3)
            obj.SearchNumber(this->m_username, 2, recvsockCli);
        else if (op == 4)
            obj.SearchTime1(this->m_username, 2, recvsockCli);
        else if (op == 5)
            obj.SearchTime2(this->m_username, 2, recvsockCli);
        else {
            strcpy(sendBuf, "\n请输入合法的操作！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }

        strcpy(sendBuf, "\n请选择您要查询的内容：\n1 - 我寄出的\n2 - 我收到的\n3 - 查询快递单号\n4 - 查询发送时间\n5 - 查询签收时间\n0 - 退出查询\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        cout << recvBuf;
        reLen = SOCKET_ERROR;
        op = atoi(recvBuf);
    }
}

int Users::Count() const {
    ifstream fl;
    fl.open("./data/users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取用户数失败" << endl;
        return -1;
    }

    int count = 0;
    char temp[1024];
    while (!fl.eof()) {
        fl.getline(temp, 1024);
        count++;
    }
    fl.close();
    count--;
    return count;
}

void Users::Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<string>& t_remaining, vector<string>& t_address) const {
    ifstream fl;
    fl.open("./data/users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取用户数失败" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";
    string t5 = "";
    string t6 = "";
    for (int i = 0; i < Count(); i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;

        t_username.push_back(t1);
        t_name.push_back(t2);
        t_phone.push_back(t3);
        t_password.push_back(t4);
        t_remaining.push_back(t5);
        t_address.push_back(t6);

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";
        t5 = "";
        t6 = "";
    }
    fl.close();
}

void Users::SaveInfo(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;

    ofstream write;
    write.open("./data/users.txt", ios::app);
    if (!write.is_open()) {
        cout << "信息保存失败！" << endl;
        return;
    }
    write << this->m_username << ' '
        << this->m_name << ' '
        << this->m_phone << ' '
        << this->m_password << ' '
        << this->m_remaining << ' '
        << this->m_address
        << endl;
    strcpy(sendBuf, "\n信息保存成功！\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;
}

void Users::UpdateInfo() const {
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<string> t_remaining;//账户余额
    vector<string> t_address;//地址

    Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);
    int number = 0;
    for (int i = 0; i < t_username.size(); i++) {
        if (this->m_username == t_username[i]) {
            number = i;
            break;
        }
    }
    t_name[number] = this->m_name;
    t_phone[number] = this->m_phone;
    t_password[number] = this->m_password;
    stringstream ss;
    ss << this->m_remaining;
    t_remaining[number] = ss.str();
    t_address[number] = this->m_address;

    ofstream change;
    change.open("./data/users.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("./data/users.txt", ios::app);
    if (!write.is_open()) {
        cout << "信息更新失败！" << endl;
        return;
    }
    for (int i = 0; i < t_username.size(); i++) {
        write << t_username[i] << ' '
            << t_name[i] << ' '
            << t_phone[i] << ' '
            << t_password[i] << ' '
            << t_remaining[i] << ' '
            << t_address[i] << endl;
    }
    write.close();
}