#include "Courier.h"
#include "Users.h"
#include "Manager.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"

Courier::Courier() {
    this->m_username = "";
    this->m_name = "";
    this->m_phone = "";
    this->m_password = "";
    this->m_remaining = 0;
}

Courier::~Courier() {}

int Courier::Count() const {
    ifstream fl;
    fl.open("couriers.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取快递员信息失败" << endl;
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

void Courier::Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<double>& t_remaining) const {
    ifstream fl;
    fl.open("couriers.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取快递员信息失败" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";
    double t5 = 0;
    for (int i = 0; i < Count(); i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;

        t_username.push_back(t1);
        t_name.push_back(t2);
        t_phone.push_back(t3);
        t_password.push_back(t4);
        t_remaining.push_back(t5);

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";
        t5 = 0;
    }
    fl.close();
}

int Courier::LogIn3() {
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

    Info(t_username, t_name, t_phone, t_password, t_remaining);

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
        cout << "\n登陆成功！\n您好！" << endl;
        return 1;
    }
    else {
        cout << "\n请输入正确的用户名和密码！" << endl;
        return 0;
    }
}

void Courier::SetCourier() {
    cout << "请输入快递员信息：" << endl;
    cout << "用户名：";
    cin >> this->m_username;
    cout << "姓名：";
    cin >> this->m_name;
    cout << "联系方式：";
    cin >> this->m_phone;
    cout << "预置密码：";
    cin >> this->m_password;
    this->m_remaining = 0;
    SaveInfo();
    cout << "\n快递员添加成功！" << endl;
}

void Courier::RemoveCourier() const {
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额

    Info(t_username, t_name, t_phone, t_password, t_remaining);

    string d_username;
    cout << "\n请输入要删除的快递员用户名：";
    cin >> d_username;

    int index = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (d_username == t_username[i]) {
            index = i;
            break;
        }
    }
    if (index == -1)
        cout << "\n该快递员不存在！" << endl;
    else {
        ofstream change;
        change.open("couriers.txt", ios::trunc | ios::out);
        change.close();
        ofstream write;
        write.open("couriers.txt", ios::app);
        if (!write.is_open()) {
            cout << "快递员信息删除失败！" << endl;
            return;
        }
        for (int i = 0; i < t_username.size(); i++) {
            if (d_username != t_username[i]) {
                write << t_username[i] << ' '
                    << t_name[i] << ' '
                    << t_phone[i] << ' '
                    << t_password[i] << ' '
                    << t_remaining[i] << endl;
            }
        }
        write.close();
        cout << "\n快递员信息删除成功！" << endl;
    }
}

void Courier::SendDel() {
    cout << "\n您正在揽收快递！" << endl;


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

    Objects obj;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);
    int isex = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_state[i] == 2 && t_cour[i] == this->m_username) {
            isex += 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i]
                << "\n寄件时间：" << t_time1[i]
                << "\n物品分类：";
            if (t_type[i] == 1)
                cout << "易碎品";
            else if (t_type[i] == 2)
                cout << "图书";
            else if (t_type[i] == 3)
                cout << "普通快递";
            cout << "\n快递重量：" << t_weight[i]
                << "\n备注：" << t_description[i]
                << endl;

        }
    }

    if (isex == 0) {
        cout << "\n没有待揽收的快递！\n" << endl;
        return;
    }

    cout << "请输入您要揽收的快递单号：";
    string send = "";
    cin >> send;

    double price = 0;
    Manager manager;
    for (int i = 0; i < t_number.size(); i++) {
        if (t_number[i] == send && t_state[i] == 2 && t_cour[i] == this->m_username) {
            if (t_type[i] == 1) {
                Fragile ob;
                ob.m_number = send;
                ob.m_state = 1;
                ob.m_time2 = "暂无";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(t_weight[i]);
            }
            else if (t_type[i] == 2) {
                Book ob;
                ob.m_number = send;
                ob.m_state = 1;
                ob.m_time2 = "暂无";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(t_weight[i]);
            }
            else if (t_type[i] == 3) {
                Ordinary ob;
                ob.m_number = send;
                ob.m_state = 1;
                ob.m_time2 = "暂无";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(t_weight[i]);
            }
            isex -= 1;
            cout << "\n揽收成功！" << endl;
            break;
        }
    }

    if (isex == 0) {
        cout << "\n没有待揽收的快递！\n" << endl;
        return;
    }

    cout << "\n是否继续揽收快递？\n1 - 继续揽收快递\t0 - 退出" << endl;
    int iscon;
    cin >> iscon;
    while (iscon == 1) {
        send = "";
        cout << "请输入您要揽收的快递单号：";
        cin >> send;


        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == send && t_state[i] == 2 && t_cour[i] == this->m_username) {
                if (t_type[i] == 1) {
                    Fragile ob;
                    ob.m_number = send;
                    ob.m_state = 1;
                    ob.m_time2 = "暂无";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(t_weight[i]);
                }
                else if (t_type[i] == 2) {
                    Book ob;
                    ob.m_number = send;
                    ob.m_state = 1;
                    ob.m_time2 = "暂无";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(t_weight[i]);
                }
                else if (t_type[i] == 3) {
                    Ordinary ob;
                    ob.m_number = send;
                    ob.m_state = 1;
                    ob.m_time2 = "暂无";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(t_weight[i]);
                }
                isex -= 1;
                cout << "\n揽收成功！" << endl;
                break;

            }
        }

        if (isex == 0) {
            cout << "\n没有待揽收的快递！\n" << endl;
            return;
        }

        cout << "\n是否继续揽收快递？\n1 - 继续揽收快递\t0 - 退出" << endl;
        cin >> iscon;
    }

    manager.UpdateRemain(-1 * 0.5 * price);
    this->m_remaining = this->m_remaining + 0.5 * price;
    UpdateInfo();
}

void Courier::SearchDel() const {
    cout << "\n请选择您要查询的内容：" << endl;
    cout << "1 - 我揽收的\n2 - 我投递的\n3 - 查询寄件人\n4 - 查询收件人\n5 - 查询寄件时间\n6 - 查询收件时间\n7 - 查询快递单号\n0 - 退出" << endl;
    int op;
    cin >> op;
    Objects obj;
    while (op) {
        switch (op) {
        case 1:     SearchS1();     break;
        case 2:     SearchS0();     break;
        case 3:     SearchUser1();  break;
        case 4:     SearchUser2();  break;
        case 5:     SearchT1();     break;
        case 6:     SearchT2();     break;
        case 7:     SearchNum();    break;
        case 0:     break;
        default:    cout << "\n请输入合法的操作选项！\n" << endl;
        }
        cout << "\n请选择您要查询的内容：" << endl;
        cout << "1 - 我揽收的\n2 - 我投递的\n3 - 查询寄件人\n4 - 查询收件人\n5 - 查询寄件时间\n6 - 查询收件时间\n7 - 查询快递单号\n0 - 退出" << endl;
        cin >> op;
    }
}

void Courier::SearchS1() const {
    Objects ob;
    ob.SearchState1(this->m_username);
}

void Courier::SearchS0() const {
    Objects ob;
    ob.SearchState0(this->m_username);
}

void Courier::SearchUser1() const {
    Objects ob;
    string username;
    cout << "请输入您要查询的寄件人用户名：";
    cin >> username;
    ob.MyExpress(username);
}

void Courier::SearchUser2() const {
    Objects ob;
    string username;
    cout << "请输入您要查询的收件人用户名：";
    cin >> username;
    ob.MyReceive(username);
}

void Courier::SearchT1() const {
    Objects ob;
    ob.SearchTime1(this->m_username, 3);
}

void Courier::SearchT2() const {
    Objects ob;
    ob.SearchTime2(this->m_username, 3);
}

void Courier::SearchNum() const {
    Objects ob;
    ob.SearchNumber(this->m_username, 3);
}

void Courier::SaveInfo() const {
    ofstream write;
    write.open("couriers.txt", ios::app);
    if (!write.is_open()) {
        cout << "快递员信息保存失败！" << endl;
        return;
    }
    write << this->m_username << ' '
        << this->m_name << ' '
        << this->m_phone << ' '
        << this->m_password << ' '
        << this->m_remaining
        << endl;
}

void Courier::UpdateInfo() const {
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额

    Info(t_username, t_name, t_phone, t_password, t_remaining);
    int number;
    for (int i = 0; i < t_username.size(); i++) {
        if (this->m_username == t_username[i]) {
            number = i;
            break;
        }
    }
    //t_name[number] = this->m_name;
    //t_phone[number] = this->m_phone;
    //t_password[number] = this->m_password;
    t_remaining[number] = this->m_remaining;

    ofstream change;
    change.open("couriers.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("couriers.txt", ios::app);
    if (!write.is_open()) {
        cout << "快递员信息更新失败！" << endl;
        return;
    }
    for (int i = 0; i < t_username.size(); i++) {
        write << t_username[i] << ' '
            << t_name[i] << ' '
            << t_phone[i] << ' '
            << t_password[i] << ' '
            << t_remaining[i] << endl;
    }
    write.close();

}