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
        cout << "��ȡ���Ա��Ϣʧ��" << endl;
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
        cout << "��ȡ���Ա��Ϣʧ��" << endl;
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

    cout << "\n�û�����";
    cin >> username;
    cout << "���룺";
    cin >> password;


    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����

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
        cout << "\n��½�ɹ���\n���ã�" << endl;
        return 1;
    }
    else {
        cout << "\n��������ȷ���û��������룡" << endl;
        return 0;
    }
}

void Courier::SetCourier() {
    cout << "��������Ա��Ϣ��" << endl;
    cout << "�û�����";
    cin >> this->m_username;
    cout << "������";
    cin >> this->m_name;
    cout << "��ϵ��ʽ��";
    cin >> this->m_phone;
    cout << "Ԥ�����룺";
    cin >> this->m_password;
    this->m_remaining = 0;
    SaveInfo();
    cout << "\n���Ա��ӳɹ���" << endl;
}

void Courier::RemoveCourier() const {
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����

    Info(t_username, t_name, t_phone, t_password, t_remaining);

    string d_username;
    cout << "\n������Ҫɾ���Ŀ��Ա�û�����";
    cin >> d_username;

    int index = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (d_username == t_username[i]) {
            index = i;
            break;
        }
    }
    if (index == -1)
        cout << "\n�ÿ��Ա�����ڣ�" << endl;
    else {
        ofstream change;
        change.open("couriers.txt", ios::trunc | ios::out);
        change.close();
        ofstream write;
        write.open("couriers.txt", ios::app);
        if (!write.is_open()) {
            cout << "���Ա��Ϣɾ��ʧ�ܣ�" << endl;
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
        cout << "\n���Ա��Ϣɾ���ɹ���" << endl;
    }
}

void Courier::SendDel() {
    cout << "\n���������տ�ݣ�" << endl;


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
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i]
                << "\n�ļ�ʱ�䣺" << t_time1[i]
                << "\n��Ʒ���ࣺ";
            if (t_type[i] == 1)
                cout << "����Ʒ";
            else if (t_type[i] == 2)
                cout << "ͼ��";
            else if (t_type[i] == 3)
                cout << "��ͨ���";
            cout << "\n���������" << t_weight[i]
                << "\n��ע��" << t_description[i]
                << endl;

        }
    }

    if (isex == 0) {
        cout << "\nû�д����յĿ�ݣ�\n" << endl;
        return;
    }

    cout << "��������Ҫ���յĿ�ݵ��ţ�";
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
                ob.m_time2 = "����";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(t_weight[i]);
            }
            else if (t_type[i] == 2) {
                Book ob;
                ob.m_number = send;
                ob.m_state = 1;
                ob.m_time2 = "����";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(t_weight[i]);
            }
            else if (t_type[i] == 3) {
                Ordinary ob;
                ob.m_number = send;
                ob.m_state = 1;
                ob.m_time2 = "����";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(t_weight[i]);
            }
            isex -= 1;
            cout << "\n���ճɹ���" << endl;
            break;
        }
    }

    if (isex == 0) {
        cout << "\nû�д����յĿ�ݣ�\n" << endl;
        return;
    }

    cout << "\n�Ƿ�������տ�ݣ�\n1 - �������տ��\t0 - �˳�" << endl;
    int iscon;
    cin >> iscon;
    while (iscon == 1) {
        send = "";
        cout << "��������Ҫ���յĿ�ݵ��ţ�";
        cin >> send;


        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == send && t_state[i] == 2 && t_cour[i] == this->m_username) {
                if (t_type[i] == 1) {
                    Fragile ob;
                    ob.m_number = send;
                    ob.m_state = 1;
                    ob.m_time2 = "����";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(t_weight[i]);
                }
                else if (t_type[i] == 2) {
                    Book ob;
                    ob.m_number = send;
                    ob.m_state = 1;
                    ob.m_time2 = "����";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(t_weight[i]);
                }
                else if (t_type[i] == 3) {
                    Ordinary ob;
                    ob.m_number = send;
                    ob.m_state = 1;
                    ob.m_time2 = "����";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(t_weight[i]);
                }
                isex -= 1;
                cout << "\n���ճɹ���" << endl;
                break;

            }
        }

        if (isex == 0) {
            cout << "\nû�д����յĿ�ݣ�\n" << endl;
            return;
        }

        cout << "\n�Ƿ�������տ�ݣ�\n1 - �������տ��\t0 - �˳�" << endl;
        cin >> iscon;
    }

    manager.UpdateRemain(-1 * 0.5 * price);
    this->m_remaining = this->m_remaining + 0.5 * price;
    UpdateInfo();
}

void Courier::SearchDel() const {
    cout << "\n��ѡ����Ҫ��ѯ�����ݣ�" << endl;
    cout << "1 - �����յ�\n2 - ��Ͷ�ݵ�\n3 - ��ѯ�ļ���\n4 - ��ѯ�ռ���\n5 - ��ѯ�ļ�ʱ��\n6 - ��ѯ�ռ�ʱ��\n7 - ��ѯ��ݵ���\n0 - �˳�" << endl;
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
        default:    cout << "\n������Ϸ��Ĳ���ѡ�\n" << endl;
        }
        cout << "\n��ѡ����Ҫ��ѯ�����ݣ�" << endl;
        cout << "1 - �����յ�\n2 - ��Ͷ�ݵ�\n3 - ��ѯ�ļ���\n4 - ��ѯ�ռ���\n5 - ��ѯ�ļ�ʱ��\n6 - ��ѯ�ռ�ʱ��\n7 - ��ѯ��ݵ���\n0 - �˳�" << endl;
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
    cout << "��������Ҫ��ѯ�ļļ����û�����";
    cin >> username;
    ob.MyExpress(username);
}

void Courier::SearchUser2() const {
    Objects ob;
    string username;
    cout << "��������Ҫ��ѯ���ռ����û�����";
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
        cout << "���Ա��Ϣ����ʧ�ܣ�" << endl;
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
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����

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
        cout << "���Ա��Ϣ����ʧ�ܣ�" << endl;
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