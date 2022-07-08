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

#pragma warning(disable:4996)

Objects::Objects() {
    this->m_number = "";//��ݵ���
    this->m_time1 = "";//����ʱ��
    this->m_time2 = "";//����ʱ��
    this->m_user1 = "";//�ļ��û�
    this->m_user2 = "";//�ռ��û�
    this->m_state = -1;//��Ʒ״̬��0-��ǩ�գ� 1-��ǩ��
    this->m_description = "";//��Ʒ����
}

Objects::~Objects() {}

/*
void Objects::SetObjects(){
    string number;//��ݵ���
    string user1;//�ļ��û�
    string user2;//�ռ��û�
    int state;//��Ʒ״̬��0-��ǩ�գ� 1-��ǩ��
    string time1;//����ʱ��
    string time2;//����ʱ��
    string description;//��Ʒ����

    cout << "��ݵ��ţ�";
    cin >> number;
    this->m_number = number;

    cout << "�ļ��ˣ�";
    cin >> user1;
    this->m_user1 = user1;
    cout << "�ռ��ˣ�";
    cin >> user2;
    this->m_user2 = user2;

    cout << "���״̬(0Ϊ��ǩ�գ�1Ϊ��ǩ��)��";
    cin >>state;
    this->m_state = state;

    cout << "����ʱ��";
    cin >> time1;
    this->m_time1 = time1;
    if(state == 1){
        cout << "����ʱ�䣺����" << endl;
        time2 = "����";
    }
    else{
        cout << "����ʱ�䣺";
        cin >> time2;
    }
    this->m_time2 = time2;

    cout << "��Ʒ������";
    cin >> description;
    this->m_description = description;

    SaveObjects();
}
*/

string Objects::GetNum() const {
    time_t now = time(0);
    stringstream ss;
    string num = "";
    string t1 = "";
    string t2 = "";

    ss << now;
    ss >> t1;
    ss.clear();
    int n = CountObjects() + 1;
    ss << n;
    ss >> t2;
    ss.clear();

    num += t1;
    num += t2;

    return num;
}

string Objects::GetTime() const {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    string t = "";
    string year = "";
    string month = "";
    string day = "";
    string hour = "";
    string min = "";

    ss << (1900 + ltm->tm_year);
    ss >> year;
    ss.clear();

    ss << (1 + ltm->tm_mon);
    ss >> month;
    ss.clear();

    ss << ltm->tm_mday;
    ss >> day;
    ss.clear();

    ss << ltm->tm_hour;
    ss >> hour;
    ss.clear();

    ss << ltm->tm_min;
    ss >> min;
    ss.clear();

    t += year;
    t += "��";
    t += month;
    t += "��";
    t += day;
    t += "��";
    t += hour;
    t += ":";
    t += min;

    return t;

}

void Objects::MyExpress(string username) const {
    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_user1[i] == username) {
            isin = 1;
            cout << "��ݵ��ţ�" << t_number[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << "\n" << endl;
        }
    }

    if (isin == 0)
        cout << "\n����ʷ��¼��\n" << endl;

}

void Objects::MyReceive(string username) const {
    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_user2[i] == username) {
            isin = 1;
            cout << "��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << "\n" << endl;
        }
    }

    if (isin == 0)
        cout << "\n����ʷ��¼��\n" << endl;

}

void Objects::SearchNumber(string username) const {

    string number;
    cout << "��������Ҫ��ѯ�Ŀ�ݵ��ţ�";
    cin >> number;
    cout << "\n����Ϊ����ѯ�����Ժ󡭡�\n" << endl;

    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_number[i] == number && (t_user1[i] == username || t_user2[i] == username)) {
            isin = 1;
            cout << "��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << "\n" << endl;
            break;
        }
    }

    if (isin == 0)
        cout << "�ⲻ�����Ŀ�ݻ��ݲ����ڣ�\n" << endl;
}

void Objects::SearchTime1(string username) const {

    string time1;
    cout << "\n��������Ҫ��ѯ�Ŀ�ݷ���ʱ�䣺";
    cin >> time1;
    cout << "\n����Ϊ����ѯ�����Ժ󡭡�\n" << endl;

    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_time1[i] == time1 && (t_user1[i] == username || t_user2[i] == username)) {
            isin = 1;
            cout << "��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << "\n" << endl;
        }
    }

    if (isin == 0)
        cout << "�ⲻ�����Ŀ�ݻ��ݲ����ڣ�\n" << endl;

}

void Objects::SearchTime2(string username) const {

    string time2;
    cout << "\n��������Ҫ��ѯ�Ŀ��ǩ��ʱ�䣺";
    cin >> time2;
    cout << "\n����Ϊ����ѯ�����Ժ󡭡�\n" << endl;
    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);

    int isin = 0;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_time2[i] == time2 && (t_user1[i] == username || t_user2[i] == username)) {
            isin = 1;
            cout << "��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if (t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if (t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << "\n"
                << endl;
        }
    }

    if (isin == 0)
        cout << "�ⲻ�����Ŀ�ݻ��ݲ����ڣ�\n" << endl;

}

void Objects::SaveObjects() const {
    ofstream write;
    write.open("objects.txt", ios::app);
    if (!write.is_open()) {
        cout << "�����Ϣ����ʧ�ܣ�" << endl;
        return;
    }
    write << this->m_number << ' '
        << this->m_user1 << ' '
        << this->m_user2 << ' '
        << this->m_state << ' '
        << this->m_time1 << ' '
        << this->m_time2 << ' '
        << this->m_description
        << endl;
    //cout << "�����Ϣ����ɹ���" << endl;
}

void Objects::UpdateObjects() const {
    vector<string> t_number;
    vector<string> t_user1;
    vector<string> t_user2;
    vector<int> t_state;
    vector<string> t_time1;
    vector<string> t_time2;
    vector<string> t_description;
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_description);
    int index;
    for (int i = 0; i < t_number.size(); i++) {
        if (this->m_number == t_number[i]) {
            index = i;
            break;
        }
    }
    t_state[index] = this->m_state;
    t_time2[index] = this->m_time2;

    ofstream change;
    change.open("objects.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("objects.txt", ios::app);
    if (!write.is_open()) {
        cout << "�����Ϣ����ʧ�ܣ�" << endl;
        return;
    }
    for (int i = 0; i < t_number.size(); i++) {
        write << t_number[i] << ' '
            << t_user1[i] << ' '
            << t_user2[i] << ' '
            << t_state[i] << ' '
            << t_time1[i] << ' '
            << t_time2[i] << ' '
            << t_description[i]
            << endl;
    }
    write.close();
}

void Objects::ShowObjects(vector<string>& t_number, vector<string>& t_user1, vector<string>& t_user2, vector<int>& t_state, vector<string>& t_time1, vector<string>& t_time2, vector<string>& t_description) const {
    ifstream fl;
    fl.open("objects.txt", ios::in);
    if (!fl.is_open()) {
        cout << "��ȡ�����Ϣʧ��" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    int t4 = -1;
    string t5 = "";
    string t6 = "";
    string t7 = "";
    for (int i = 0; i < CountObjects(); i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;
        fl >> t6;
        fl >> t7;

        t_number.push_back(t1);
        t_user1.push_back(t2);
        t_user2.push_back(t3);
        t_state.push_back(t4);
        t_time1.push_back(t5);
        t_time2.push_back(t6);
        t_description.push_back(t7);

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

int Objects::CountObjects() const {
    ifstream fl;
    fl.open("objects.txt", ios::in);
    if (!fl.is_open()) {
        cout << "��ȡ�����ʧ��" << endl;
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