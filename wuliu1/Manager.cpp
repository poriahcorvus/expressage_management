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

    cout << "\n�û�����";
    cin >> username;
    cout << "���룺";
    cin >> password;

    string t_username;//�û���
    string t_name;//����
    string t_password;//����
    double t_remaining;//�˻����

    ifstream fl;
    fl.open("manager.txt", ios::in);
    if (!fl.is_open()) {
        cout << "��ȡ����Ա��Ϣʧ��" << endl;
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
        cout << "\n��½�ɹ���\n����Ա���ã�" << endl;
        return 1;
    }
    else {
        cout << "\n��������ȷ���û��������룡\n" << endl;
        return 0;
    }
}

void Manager::UsInfo() const {
    cout << "\n�����ڲ鿴�����û���Ϣ��\n" << endl;
    ifstream fl;
    fl.open("users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "�鿴�û���Ϣʧ�ܣ�" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";//���벻��ʾ
    double t5 = 0;
    string t6 = "";
    Users user;
    int number = user.Count();
    cout << "�û�����" << number << '\n' << endl;
    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;

        cout << "�û�����" << t1
            << "\n������" << t2
            << "\n��ϵ��ʽ��" << t3
            << "\n�˻���" << t5
            << "\n��ַ��" << t6
            << '\n' << endl;

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";//���벻��ʾ
        t5 = 0;
        t6 = "";
    }
    fl.close();
}

void Manager::ObInfo() const {
    cout << "\n�����ڲ鿴���п����Ϣ��\n" << endl;
    ifstream fl;
    fl.open("objects.txt", ios::in);
    if (!fl.is_open()) {
        cout << "�鿴�����Ϣʧ�ܣ�" << endl;
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
    cout << "���п������" << number << '\n' << endl;
    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;
        fl >> t7;

        cout << "\n��ݵ��ţ�" << t1
            << "\n�ռ��ˣ�" << t2
            << "\n�ļ��ˣ�" << t3
            << "\n���������" << t7;
        if (t4 == 1) {
            cout << "\n�������������" << endl;
        }
        else if (t4 == 0) {
            cout << "\n������ʹ�" << endl;
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
    cout << "\n��ѡ����Ҫ��ѯ�����ݣ�" << endl;
    cout << "1 - �û�\n2 - ��ѯ��ݵ���\n3 - ��ѯ����ʱ��\n4 - ��ѯǩ��ʱ��\n0 - �˳���ѯ" << endl;
    int op;
    cin >> op;
    switch (op) {
    case 1:     SearchUser();       break;
    case 2:     SearchNumber();     break;
    case 3:     SearchTime_1();     break;
    case 4:     SearchTime_2();     break;
    case 0:     break;
    default:    cout << "\n������Ϸ��Ĳ�����" << endl;
    }
    while (op) {
        cout << "\n��ѡ����Ҫ��ѯ�����ݣ�" << endl;
        cout << "1 - �û�\n2 - ��ѯ��ݵ���\n3 - ��ѯ����ʱ��\n4 - ��ѯǩ��ʱ��\n0 - �˳���ѯ" << endl;
        cin >> op;
        switch (op) {
        case 1:     SearchUser();       break;
        case 2:     SearchNumber();     break;
        case 3:     SearchTime_1();     break;
        case 4:     SearchTime_2();     break;
        case 0:     break;
        default:    cout << "\n������Ϸ��Ĳ�����" << endl;
        }
    }
}

void Manager::SearchUser() const {
    cout << "\n��������Ҫ��ѯ���û�����";
    Users user;
    cin >> user.m_username;

    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����
    vector<string> t_address;//��ַ

    user.Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);
    int number = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (user.m_username == t_username[i]) {
            number = i;
            break;
        }
    }

    if (number == -1) {
        cout << "\n���û������ڣ�" << endl;
        return;
    }

    cout << "\n�û�����" << t_username[number]
        << "\n������" << t_name[number]
        << "\n��ϵ��ʽ��" << t_phone[number]
        << "\n�˻���" << t_remaining[number]
        << "\n��ַ��" << t_address[number]
        << '\n' << endl;

    Objects obj;
    cout << "\n���û��ĳ��İ�����" << endl;
    obj.MyExpress(user.m_username);
    cout << "\n���û��յ��İ�����" << endl;
    obj.MyReceive(user.m_username);

}

void Manager::SearchNumber() const {
    Objects obj;
    string number;
    cout << "\n��������Ҫ��ѯ�Ŀ�ݵ��ţ�";
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
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << endl;
            break;
        }
    }

    if (isin == 0)
        cout << "\n��ݲ����ڣ�\n" << endl;
}

void Manager::SearchTime_1() const {
    Objects obj;
    string time1;
    cout << "\n��������Ҫ��ѯ�Ŀ�ݷ���ʱ�䣺";
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
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << endl;
        }
    }

    if (isin == 0)
        cout << "\n����ʷ��¼��\n" << endl;

}

void Manager::SearchTime_2() const {
    Objects obj;
    string time2;
    cout << "\n��������Ҫ��ѯ�Ŀ��ǩ��ʱ�䣺";
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
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << endl;
        }
    }

    if (isin == 0)
        cout << "\n����ʷ��¼��\n" << endl;

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
        cout << "��ȡ����Ա��Ϣʧ��" << endl;
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
        cout << "����Ա��Ϣ����ʧ�ܣ�" << endl;
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

    cout << "�û�����";
    cin >> username;
    cout << "������";
    cin >> name;
    cout << "���룺";
    cin >> password;
    cout << "���룺";
    cin >> remaining;

    fstream write;
    write.open("manager.txt", ios::out | ios::app);
    if(!write.is_open()){
        cout << "����Ա��Ϣ����ʧ�ܣ�" << endl;
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
        cout << "��ȡ�û���ʧ��" << endl;
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
        cout << "��ȡ�����ʧ��" << endl;
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