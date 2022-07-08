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
    cout << "\n�û�����";
    cin >> username;
    cout << "���룺";
    cin >> password;

    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����
    vector<string> t_address;//��ַ

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
        cout << "\n��½�ɹ���" << endl;
        return 1;
    }
    else {
        cout << "\n��������ȷ���û��������룡" << endl;
        return 0;
    }
}

void Users::SignUp() {
    string username;
    string password1;
    string password2;
    cout << "������һ���û���:";
    cin >> username;

    int num = Count();
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����
    vector<string> t_address;//��ַ
    Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);

    int us_flag = 0;
    for (int i = 0; i < num; i++) {
        if (username == t_username[i]) {
            us_flag = 1;
            break;
        }
    }
    while (us_flag) {
        cout << "�û����Ѵ��ڣ�" << endl;
        cout << "������һ���û�����";
        cin >> username;
        us_flag = 0;
        for (int i = 0; i < num; i++) {
            if (username == t_username[i]) {
                us_flag = 1;
                break;
            }
        }
    }

    cout << "���������룺";
    cin >> password1;
    cout << "��ȷ�����룺";
    cin >> password2;
    while (password1 != password2) {
        cout << "�������벻һ��\n������ȷ�����룺";
        cin >> password2;
    }

    this->m_username = username;
    this->m_password = password1;


    cout << "ע��ɹ���\n���������ĸ�����Ϣ��" << endl;
    SetMess();
    SaveInfo();
    cout << "�����µ�¼����֤��ݣ�" << endl;
}

void Users::SetMess() {
    string name;
    string phone;
    string address;

    cout << "����������";
    cin >> name;
    this->m_name = name;
    cout << "�����ֻ��ţ�";
    cin >> phone;
    this->m_phone = phone;
    cout << "���ĵ�ַ��";
    cin >> address;
    this->m_address = address;
}

void Users::ChangePass() {
    string new_password;
    string n_password;

    cout << "�������޸����룡" << endl;
    cout << "�����������룺";
    cin >> new_password;
    cout << "��ȷ�����룺";
    cin >> n_password;
    while (new_password != n_password) {
        cout << "�������벻һ��\n������ȷ�����룺";
        cin >> n_password;
    }

    cout << "�����޸ĳɹ���" << endl;
    this->m_password = new_password;
    UpdateInfo();
}

void Users::CheckRemain() const {
    cout << "\n����Ϊ����ѯ�˻����!\n" << endl;

    cout << "�����˻����Ϊ��" << this->m_remaining << endl;
}

void Users::TopUp() {
    cout << "\n��������Ҫ��ֵ�Ľ���������";
    int add;
    cin >> add;
    this->m_remaining += add;

    cout << "\n��ֵ�ɹ���" << endl;

    cout << "\n�����˻����Ϊ��" << this->m_remaining << '\n' << endl;
    UpdateInfo();
}

void Users::ExpressDel() {
    cout << "\n���������뷢�Ϳ��" << endl;

    cout << "\n��ѡ������Ʒ���ࣺ\n1 - ����Ʒ\t2 - ͼ��\t3 - ��ͨ��Ʒ" << endl;
    int tp;
    cin >> tp;
    if (tp == 1) {
        Fragile ob;
        Express(ob);
        double price = ob.GetPrice(ob.m_weight);
        if (this->m_remaining >= price) {
            ob.SaveObjects();
            cout << "\n������ڵȴ����գ�\n" << endl;
            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price);
        }
        else
            cout << "\n���㣬���ֵ��" << endl;

    }
    else if (tp == 2) {
        Book ob;
        Express(ob);
        double price = ob.GetPrice(ob.m_weight);
        if (this->m_remaining >= price) {
            ob.SaveObjects();
            cout << "\n������ڵȴ����գ�\n" << endl;
            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price);
        }
        else
            cout << "\n���㣬���ֵ��" << endl;
    }

    else if (tp == 3) {
        Ordinary ob;
        Express(ob);
        double price = ob.GetPrice(ob.m_weight);
        if (this->m_remaining >= price) {
            ob.SaveObjects();
            cout << "\n������ڵȴ����գ�\n" << endl;
            this->m_remaining = this->m_remaining - price;
            UpdateInfo();
            Manager m;
            m.UpdateRemain(price);
        }
        else
            cout << "\n���㣬���ֵ��" << endl;
    }
}

void Users::Express(Objects& ob) {
    ob.m_number = ob.GetNum();
    ob.m_user1 = this->m_username;
    cout << "�������ռ����û�����";
    cin >> ob.m_user2;
    ob.m_state = 2;//0-��ǩ�գ�1-��ǩ�գ� 2-������
    ob.m_time1 = ob.GetTime();
    ob.m_time2 = "����";
    ob.m_cour = "����";
    cout << "��������������";
    cin >> ob.m_weight;
    cout << "�������ݱ�ע��";
    cin >> ob.m_description;
}

void Users::ReceiveDel() const {
    cout << "\n������ǩ�տ��\n" << endl;


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
            cout << "��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n��Ʒ���";
            if (t_type[i] == 1)  cout << "����Ʒ";
            if (t_type[i] == 2)  cout << "ͼ��";
            if (t_type[i] == 3)  cout << "��ͨ��Ʒ";
            cout << "\n��ע��" << t_description[i]
                << '\n' << endl;

        }
    }
    if (isex == 0) {
        cout << "\nû�д�ǩ�յĿ��!\n";
        return;
    }
    cout << "\n��ѡ��Ҫǩ�յĿ�ݣ����뵥�ţ���";
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

            cout << "\nǩ�ճɹ���" << endl;
            break;
        }
    }

    if (isex == 0) {
        cout << "\nû�д�ǩ�յĿ��!\n";
        return;
    }

    cout << "\n�Ƿ����ǩ�տ�ݣ�\n1 - ����ǩ�տ��\t0 - �˳�" << endl;
    int iscon;
    cin >> iscon;
    while (iscon == 1) {
        acc = "";
        tm = "";
        cout << "\n��ѡ��Ҫǩ�յĿ�ݣ����뵥�ţ���";
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

                cout << "\nǩ�ճɹ���" << endl;
                break;
            }
        }

        if (isex == 0) {
            cout << "\nû�д�ǩ�յĿ��!\n";
            return;
        }

        cout << "\n�Ƿ����ǩ�տ�ݣ�\n1 - ����ǩ�տ��\t0 - �˳�" << endl;
        cin >> iscon;
    }
}

void Users::SearchDel() const {

    cout << "\n��ѡ����Ҫ��ѯ�����ݣ�" << endl;
    cout << "1 - �Ҽĳ���\n2 - ���յ���\n3 - ��ѯ��ݵ���\n4 - ��ѯ����ʱ��\n5 - ��ѯǩ��ʱ��\n0 - �˳���ѯ" << endl;
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
        default:    cout << "������Ϸ��Ĳ�����" << endl;
        }

        cout << "\n��ѡ����Ҫ��ѯ�����ݣ�" << endl;
        cout << "1 - �Ҽĳ���\n2 - ���յ���\n3 - ��ѯ��ݵ���\n4 - ��ѯ����ʱ��\n5 - ��ѯǩ��ʱ��\n0 - �˳���ѯ" << endl;
        cin >> op;
    }
}

int Users::Count() const {
    ifstream fl;
    fl.open("users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "��ȡ�û���ʧ��" << endl;
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
        cout << "��ȡ�û���ʧ��" << endl;
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
        cout << "��Ϣ����ʧ�ܣ�" << endl;
        return;
    }
    write << this->m_username << ' '
        << this->m_name << ' '
        << this->m_phone << ' '
        << this->m_password << ' '
        << this->m_remaining << ' '
        << this->m_address
        << endl;
    cout << "��Ϣ����ɹ���" << endl;
}

void Users::UpdateInfo() const {
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����
    vector<string> t_address;//��ַ

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
        cout << "��Ϣ����ʧ�ܣ�" << endl;
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