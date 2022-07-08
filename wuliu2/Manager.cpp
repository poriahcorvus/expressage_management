#include "Manager.h"
#include "Courier.h"
#include "Users.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"

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
    int t8 = -1;
    double t9 = 0;
    string t10 = "";

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
        fl >> t8;
        fl >> t9;
        fl >> t10;

        cout << "\n快递单号：" << t1
            << "\n寄件人：" << t2
            << "\n收件人：" << t3
            << "\n快递状态：";
        if (t4 == 0)
            cout << "已签收";
        else if (t4 == 1)
            cout << "待签收";
        else if (t4 == 2)
            cout << "待揽收";
        cout << "\n寄件时间：" << t5
            << "\n收件时间：" << t6
            << "\n快递员：" << t7
            << "\n物品分类：";
        if (t8 == 1)
            cout << "易碎品";
        else if (t8 == 2)
            cout << "图书";
        else if (t8 == 3)
            cout << "普通快递";
        cout << "\n快递重量：" << t9
            << "\n快递描述：" << t10
            << endl;


        t1 = "";
        t2 = "";
        t3 = "";
        t4 = -1;
        t5 = "";
        t6 = "";
        t7 = "";
        t8 = -1;
        t9 = 0;
        t10 = "";
    }
    fl.close();
}

void Manager::CoInfo() const {
    cout << "\n您正在查看所有快递员信息！\n" << endl;

    ifstream fl;
    fl.open("couriers.txt", ios::in);
    if (!fl.is_open()) {
        cout << "查看快递员信息失败！" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";//密码不显示
    double t5 = 0;
    Courier courier;
    int number = courier.Count();
    cout << "快递员数：" << number << '\n' << endl;
    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;

        cout << "用户名：" << t1
            << "\n姓名：" << t2
            << "\n联系方式：" << t3
            << "\n账户余额：" << t5
            << '\n' << endl;


        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";//密码不显示
        t5 = 0;
    }
    fl.close();
}

void Manager::SearchInfo() const {

    cout << "\n请选择您要查询的内容：\n" << endl;
    cout << "\n1 - 所有用户\n2 - 所有快递\n3 - 所有快递员\n\n"
        << "4 - 普通用户\n5 - 寄件人\n6 - 收件人\n7 - 寄件时间\n8 - 收件时间\n"
        << "9 - 快递员\n10 - 快递单号\n0 - 退出"
        << endl;
    int op;
    cin >> op;
    Objects ob;
    while (op) {
        switch (op) {
        case 1:     UsInfo();           break;
        case 2:     ObInfo();           break;
        case 3:     CoInfo();           break;
        case 4:     SearchUser();       break;
        case 5:     SearchExpress();    break;
        case 6:     SearchReceive();    break;
        case 7:     SearchT1();         break;
        case 8:     SearchT2();         break;
        case 9:     SearchCourier();    break;
        case 10:    SearchNum();        break;
        case 0:     break;
        default:    cout << "请输入合法的操作选项！" << endl;
        }

        cout << "\n请继续选择您要查询的内容：\n" << endl;
        cout << "\n1 - 所有用户\n2 - 所有快递\n3 - 所有快递员\n\n"
            << "4 - 普通用户\n5 - 寄件人\n6 - 收件人\n7 - 寄件时间\n8 - 收件时间\n"
            << "9 - 快递员\n10 - 快递单号\n0 - 退出"
            << endl;
        cin >> op;
    }
}

void Manager::SearchUser() const {
    cout << "\n请输入您要查询的用户名：";
    Users user;
    string username;
    cin >> username;

    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额
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
    obj.MyExpress(username);


    cout << "\n该用户收到的包裹：" << endl;
    obj.MyReceive(username);


}

void Manager::SearchExpress() const {
    cout << "请输入您要查询的寄件人用户名：";
    string username = "";
    cin >> username;

    Objects ob;
    ob.MyExpress(username);
}

void Manager::SearchReceive() const {
    cout << "请输入您要查询的收件人用户名：";
    string username = "";
    cin >> username;

    Objects ob;
    ob.MyReceive(username);
}

void Manager::SearchT1() const {
    Objects ob;
    ob.SearchTime1(this->m_username, 1);
}
void Manager::SearchT2() const {
    Objects ob;
    ob.SearchTime2(this->m_username, 1);
}

void Manager::SearchCourier() const {
    cout << "请输入要查询的快递员用户名：";
    string username;
    cin >> username;


    Courier courier;
    Objects ob;
    int index = 0;
    int isin = 0;
    vector<string> t_username;//用户名
    vector<string> t_name;//姓名
    vector<string> t_phone;//电话
    vector<string> t_password;//密码
    vector<double> t_remaining;//账户余额
    courier.Info(t_username, t_name, t_phone, t_password, t_remaining);
    for (int i = 0; i < t_username.size(); i++) {
        if (t_username[i] == username) {
            index = i;
            isin = 1;
            break;
        }
    }

    if (isin == 0) {
        cout << "\n请输入正确的快递员用户名！\n" << endl;
        return;
    }

    cout << "\n用户名：" << t_username[index]
        << "\n姓名：" << t_name[index]
        << "\n联系方式：" << t_phone[index]
        << "\n收入：" << t_remaining[index]
        << endl;

    cout << "\n该快递员已揽收的快递：" << endl;
    ob.SearchState1(username);

    cout << "\n该快递员已派送的快递：" << endl;
    ob.SearchState0(username);

}

void Manager::SearchNum() const {
    Objects ob;
    ob.SearchNumber(this->m_username, 1);
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

void Manager::UpdateRemain(double price) const {
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

    t_remaining = t_remaining + price;

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

void Manager::ManageCour() const {
    int choice;
    cout << "请选择：\n1 - 添加快递员\n2 - 删除快递员\n0 - 退出管理" << endl;
    cin >> choice;

    while (choice) {
        Courier courier;
        if (choice == 1)
            courier.SetCourier();
        else if (choice == 2)
            courier.RemoveCourier();
        cout << "\n请选择：\n1 - 添加快递员\n2 - 删除快递员\n0 - 退出管理" << endl;
        cin >> choice;

    }
}

void Manager::AllotCour() const {
    cout << "\n您正在指派快递员！" << endl;

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
        if (t_state[i] == 2 && t_cour[i] == "暂无") {
            isex += 1;
            cout << "\n快递单号：" << t_number[i]
                << "\n寄件人：" << t_user1[i]
                << "\n收件人：" << t_user2[i]
                << "\n快递分类：";
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
        cout << "\n所有快递都已经指派快递员！" << endl;
        return;
    }
    cout << "\n请输入要指派的快递单号：";
    string se = "";
    cin >> se;

    string co = "";
    int isin = 0;
    
    for (int i = 0; i < t_number.size(); i++) {
        if (t_number[i] == se) {
            isin = 1;
            isex -= 1;

            Objects ob;
            ob.m_number = se;

            cout << "\n请输入要指派的快递员：";
            cin >> co;

            ob.m_cour = co;
            ob.m_state = t_state[i];
            ob.m_time2 = t_time2[i];
            ob.UpdateObjects();

            cout << "\n指派成功！" << endl;;
            break;
        }
    }

    if (isin == 0) {
        cout << "\n请输入正确的快递单号！" << endl;
    }

    if (isex == 0) {
        cout << "\n所有快递都已经指派快递员！" << endl;
        return;
    }

    cout << "\n是否继续指派快递员？\n1 - 继续\t0 - 退出" << endl;
    int iscon = 0;
    cin >> iscon;

    while (iscon == 1) {
        se = "";
        co = "";
        isin = 0;

        cout << "\n请输入要指派的快递单号：";
        cin >> se;

        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == se) {
                isin = 1;
                isex -= 1;

                Objects ob;
                ob.m_number = se;

                cout << "\n请输入要指派的快递员：";
                cin >> co;

                ob.m_cour = co;
                ob.m_state = t_state[i];
                ob.m_time2 = t_time2[i];
                ob.UpdateObjects();

                cout << "\n指派成功！" << endl;;
                break;
            }
        }
        if (isin == 0) {
            cout << "\n请输入正确的快递单号！" << endl;
        }

        if (isex == 0) {
            cout << "\n所有快递都已经指派快递员！" << endl;
            return;
        }

        cout << "\n是否继续指派快递员？\n1 - 继续\t0 - 退出" << endl;
        cin >> iscon;
    }
}