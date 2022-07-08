#include "Users.h"
#include "Manager.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"

Users::Users() {
    this->m_username = "";
    this->m_name = "";
    this->m_phone = "";
    this->m_password = "";
    this->m_remaining = 0;
    this->m_address = "";
}
Users::~Users() {}

int Users::LogIn1() {
    string username;
    string password;
    cout << "\n用户名：";
    cin >> username;
    cout << "密码：";
    cin >> password;

    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额
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
        this->m_remaining = t_remaining[i];
        this->m_address = t_address[i];
        cout << "\n登陆成功！" << endl;
        return 1;
    }
    else {
        cout << "\n请输入正确的用户名和密码！" << endl;
        return 0;
    }
}

void Users::SignUp() {
    string username;
    string password1;
    string password2;
    cout << "请设置一个用户名:";
    cin >> username;

    int num = Count();
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额
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
        cout << "用户名已存在！" << endl;
        cout << "请设置一个用户名：";
        cin >> username;
        us_flag = 0;
        for (int i = 0; i < num; i++) {
            if (username == t_username[i]) {
                us_flag = 1;
                break;
            }
        }
    }

    cout << "请设置密码：";
    cin >> password1;
    cout << "请确认密码：";
    cin >> password2;
    while (password1 != password2) {
        cout << "两次密码不一致\n请重新确认密码：";
        cin >> password2;
    }

    this->m_username = username;
    this->m_password = password1;


    cout << "注册成功！\n请完善您的个人信息！" << endl;
    SetMess();
    SaveInfo();
    cout << "请重新登录以验证身份！" << endl;
}

void Users::SetMess() {
    string name;
    string phone;
    string address;

    cout << "您的姓名：";
    cin >> name;
    this->m_name = name;
    cout << "您的手机号：";
    cin >> phone;
    this->m_phone = phone;
    cout << "您的地址：";
    cin >> address;
    this->m_address = address;
}

void Users::ChangePass() {
    string new_password;
    string n_password;

    cout << "您正在修改密码！" << endl;
    cout << "请输入新密码：";
    cin >> new_password;
    cout << "请确认密码：";
    cin >> n_password;
    while (new_password != n_password) {
        cout << "两次密码不一致\n请重新确认密码：";
        cin >> n_password;
    }

    cout << "密码修改成功！" << endl;
    this->m_password = new_password;
    UpdateInfo();
}

void Users::CheckRemain() const {
    cout << "\n正在为您查询账户余额!\n" << endl;

    cout << "您的账户余额为：" << this->m_remaining << endl;
}

void Users::TopUp() {
    cout << "\n请输入您要充值的金额（整数）：";
    int add;
    cin >> add;
    this->m_remaining += add;

    cout << "\n充值成功！" << endl;

    cout << "\n您的账户余额为：" << this->m_remaining << '\n' << endl;
    UpdateInfo();
}

void Users::ExpressDel() {
    cout << "\n您正在申请发送快递" << endl;

    cout << "\n请选择快递物品分类：\n1 - 易碎品\t2 - 图书\t3 - 普通物品" << endl;
    int tp;
    cin >> tp;
    if (tp == 1) {
        Fragile ob;
        Express(ob);
        double price = ob.GetPrice(ob.m_weight);
        if (this->m_remaining >= price) {
            ob.SaveObjects();
            cout << "\n快递正在等待揽收！\n" << endl;
            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price);
        }
        else
            cout << "\n余额不足，请充值！" << endl;

    }
    else if (tp == 2) {
        Book ob;
        Express(ob);
        double price = ob.GetPrice(ob.m_weight);
        if (this->m_remaining >= price) {
            ob.SaveObjects();
            cout << "\n快递正在等待揽收！\n" << endl;
            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price);
        }
        else
            cout << "\n余额不足，请充值！" << endl;
    }

    else if (tp == 3) {
        Ordinary ob;
        Express(ob);
        double price = ob.GetPrice(ob.m_weight);
        if (this->m_remaining >= price) {
            ob.SaveObjects();
            cout << "\n快递正在等待揽收！\n" << endl;
            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price);
        }
        else
            cout << "\n余额不足，请充值！" << endl;
    }
}

void Users::Express(Objects& ob) {
    ob.m_number = ob.GetNum();
    ob.m_user1 = this->m_username;
    cout << "请输入收件人用户名：";
    cin >> ob.m_user2;
    ob.m_state = 2;//0-已签收，1-待签收， 2-待揽收
    ob.m_time1 = ob.GetTime();
    ob.m_time2 = "暂无";
    ob.m_cour = "暂无";
    cout << "请输入快递重量：";
    cin >> ob.m_weight;
    cout << "请输入快递备注：";
    cin >> ob.m_description;
}

void Users::ReceiveDel() const {
    cout << "\n您正在签收快递\n" << endl;


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

    Objects ob;
    ob.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);
    int isex = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_user2[i] == this->m_username && t_state[i] == 1) {
            isex += 1;
            cout << "快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n物品类别：";
            if (t_type[i] == 1)  cout << "易碎品";
            if (t_type[i] == 2)  cout << "图书";
            if (t_type[i] == 3)  cout << "普通物品";
            cout << "\n备注：" << t_description[i]
                << '\n' << endl;

        }
    }
    if (isex == 0) {
        cout << "\n没有待签收的快递!\n";
        return;
    }
    cout << "\n请选择要签收的快递（输入单号）：";
    string acc = "";
    cin >> acc;
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

            cout << "\n签收成功！" << endl;
            break;
        }
    }

    if (isex == 0) {
        cout << "\n没有待签收的快递!\n";
        return;
    }

    cout << "\n是否继续签收快递？\n1 - 继续签收快递\t0 - 退出" << endl;
    int iscon;
    cin >> iscon;
    while (iscon == 1) {
        acc = "";
        tm = "";
        cout << "\n请选择要签收的快递（输入单号）：";
        cin >> acc;
        tm = ob.GetTime();

        for (int i = 0; i < t_number.size(); i++) {
            if (t_user2[i] == this->m_username && t_state[i] == 1 && t_number[i] == acc) {
                t_state[i] = 0;
                t_time2[i] = tm;

                ob.m_number = acc;
                ob.m_state = 0;
                ob.m_time2 = tm;
                ob.m_cour = t_cour[i];
                ob.UpdateObjects();
                isex -= 0;

                cout << "\n签收成功！" << endl;
                break;
            }
        }

        if (isex == 0) {
            cout << "\n没有待签收的快递!\n";
            return;
        }

        cout << "\n是否继续签收快递？\n1 - 继续签收快递\t0 - 退出" << endl;
        cin >> iscon;
    }
}

void Users::SearchDel() const {

    cout << "\n请选择您要查询的内容：" << endl;
    cout << "1 - 我寄出的\n2 - 我收到的\n3 - 查询快递单号\n4 - 查询发送时间\n5 - 查询签收时间\n0 - 退出查询" << endl;
    int op;
    cin >> op;
    Objects obj;
    while (op) {

        switch (op) {
        case 1:     obj.MyExpress(this->m_username);    break;
        case 2:     obj.MyReceive(this->m_username);    break;
        case 3:     obj.SearchNumber(this->m_username, 2); break;
        case 4:     obj.SearchTime1(this->m_username, 2);  break;
        case 5:     obj.SearchTime2(this->m_username, 2);  break;
        case 0:     break;
        default:    cout << "请输入合法的操作！" << endl;
        }

        cout << "\n请选择您要查询的内容：" << endl;
        cout << "1 - 我寄出的\n2 - 我收到的\n3 - 查询快递单号\n4 - 查询发送时间\n5 - 查询签收时间\n0 - 退出查询" << endl;
        cin >> op;
    }
}

int Users::Count() const {
    ifstream fl;
    fl.open("users.txt", ios::in);
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

void Users::Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<double>& t_remaining, vector<string>& t_address) const {
    ifstream fl;
    fl.open("users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取用户数失败" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";
    double t5 = 0;
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
        t5 = 0;
        t6 = "";
    }
    fl.close();
}

void Users::SaveInfo() const {
    ofstream write;
    write.open("users.txt", ios::app);
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
    cout << "信息保存成功！" << endl;
}

void Users::UpdateInfo() const {
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额
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
    t_remaining[number] = this->m_remaining;
    t_address[number] = this->m_address;

    ofstream change;
    change.open("users.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("users.txt", ios::app);
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