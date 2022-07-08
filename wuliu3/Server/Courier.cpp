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
    fl.open("./data/couriers.txt", ios::in);
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

void Courier::Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<string>& t_remaining) const {
    ifstream fl;
    fl.open("./data/couriers.txt", ios::in);
    if (!fl.is_open()) {
        cout << "��ȡ���Ա��Ϣʧ��" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";
    string t5 = "";
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
        t5 = "";
    }
    fl.close();
}

int Courier::LogIn3(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n�û�����");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string username = recvBuf;
    cout << recvBuf << endl;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n���룺");
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


    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<string> t_remaining;//�˻����

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
        this->m_remaining = stod(t_remaining[i]);


        strcpy(sendBuf, "\n��½�ɹ���\n���ã�\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return 1;
    }
    else {
        strcpy(sendBuf, "\n��������ȷ���û��������룡");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return 0;
    }
}

void Courier::SetCourier(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n��������Ա��Ϣ��\n�û�����");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    this->m_username = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n������");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    this->m_name = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n��ϵ��ʽ��");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    this->m_phone = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\nԤ�����룺");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    this->m_password = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    this->m_remaining = 0;
    SaveInfo();

    strcpy(sendBuf, "\n���Ա��ӳɹ���");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;
}

void Courier::RemoveCourier(SOCKET recvsockCli) const {
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<string> t_remaining;//�˻����

    Info(t_username, t_name, t_phone, t_password, t_remaining);

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n������Ҫɾ���Ŀ��Ա�û�����");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string d_username = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    int index = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (d_username == t_username[i]) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        strcpy(sendBuf, "\n�ÿ��Ա�����ڣ�\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }
    else {
        ofstream change;
        change.open("./data/couriers.txt", ios::trunc | ios::out);
        change.close();
        ofstream write;
        write.open("./data/couriers.txt", ios::app);
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

        strcpy(sendBuf, "\n���Ա��Ϣɾ���ɹ���\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }
}

void Courier::SendDel(SOCKET recvsockCli) {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n���������տ�ݣ�\n");
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
        if (t_state[i] == 2 && t_cour[i] == this->m_username) {
            isex += 1;
            strcpy(sendBuf, "\n��ݵ��ţ�");
            strcat(sendBuf, (char*)t_number[i].c_str());
            strcat(sendBuf, "\n�ļ��ˣ�");
            strcat(sendBuf, (char*)t_user1[i].c_str());
            strcat(sendBuf, "\n�ռ��ˣ�");
            strcat(sendBuf, (char*)t_user2[i].c_str());
            strcat(sendBuf, "\n��Ʒ���ࣺ");
            if (t_type[i] == 1)
                strcat(sendBuf, "����Ʒ");
            else if (t_type[i] == 2)
                strcat(sendBuf, "ͼ��");
            else if (t_type[i] == 3)
                strcat(sendBuf, "��ͨ���");
            strcat(sendBuf, "\n���������");
            strcat(sendBuf, (char*)t_weight[i].c_str());
            strcat(sendBuf, "\n��ע��");
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
        strcpy(sendBuf, "\n�޴����յĿ�ݣ�\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }

    strcpy(sendBuf, "\n��������Ҫ���յĿ�ݵ��ţ�");
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


    double price = 0;
    Manager manager;
    for (int i = 0; i < t_number.size(); i++) {
        if (t_number[i] == se && t_state[i] == 2 && t_cour[i] == this->m_username) {
            if (t_type[i] == 1) {
                Fragile ob;
                ob.m_number = se;
                ob.m_state = 1;
                ob.m_time2 = "����";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(stod(t_weight[i]));
            }
            else if (t_type[i] == 2) {
                Book ob;
                ob.m_number = se;
                ob.m_state = 1;
                ob.m_time2 = "����";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(stod(t_weight[i]));
            }
            else if (t_type[i] == 3) {
                Ordinary ob;
                ob.m_number = se;
                ob.m_state = 1;
                ob.m_time2 = "����";
                ob.m_cour = this->m_username;
                ob.UpdateObjects();
                price = ob.GetPrice(stod(t_weight[i]));
            }
            isex -= 1;
            strcpy(sendBuf, "\n���ճɹ���\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            break;
        }
    }

    if (isex == 0) {
        strcpy(sendBuf, "\n�޴����յĿ�ݣ�\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }

    strcpy(sendBuf, "\n�Ƿ�������տ�ݣ�\n1 - �������տ��\t0 - �˳�\n");
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

        strcpy(sendBuf, "\n��������Ҫ���յĿ�ݵ��ţ�");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        se = recvBuf;
        cout << recvBuf;
        reLen = SOCKET_ERROR;

        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == se && t_state[i] == 2 && t_cour[i] == this->m_username) {
                if (t_type[i] == 1) {
                    Fragile ob;
                    ob.m_number = se;
                    ob.m_state = 1;
                    ob.m_time2 = "����";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(stod(t_weight[i]));
                }
                else if (t_type[i] == 2) {
                    Book ob;
                    ob.m_number = se;
                    ob.m_state = 1;
                    ob.m_time2 = "����";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(stod(t_weight[i]));
                }
                else if (t_type[i] == 3) {
                    Ordinary ob;
                    ob.m_number = se;
                    ob.m_state = 1;
                    ob.m_time2 = "����";
                    ob.m_cour = this->m_username;
                    ob.UpdateObjects();
                    price = ob.GetPrice(stod(t_weight[i]));
                }
                isex -= 1;
                strcpy(sendBuf, "\n���ճɹ���\n");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "0");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                break;

            }
        }

        if (isex == 0) {
            strcpy(sendBuf, "\n�޴����յĿ�ݣ�\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;

            return;
        }

        strcpy(sendBuf, "\n�Ƿ�������տ�ݣ�\n1 - �������տ��\t0 - �˳�\n");
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

    manager.UpdateRemain(-1 * 0.5 * price, recvsockCli);
    this->m_remaining = this->m_remaining + 0.5 * price;
    UpdateInfo();
}

void Courier::SearchDel(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n��ѡ����Ҫ��ѯ�����ݣ�\n1 - �����յ�\n2 - ��Ͷ�ݵ�\n3 - ��ѯ�ļ���\n4 - ��ѯ�ռ���\n5 - ��ѯ�ļ�ʱ��\n6 - ��ѯ�ռ�ʱ��\n7 - ��ѯ��ݵ���\n0 - �˳�\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    int op = atoi(recvBuf);
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    Objects obj;
    while (op) {

        if (op == 1)
            SearchS1(recvsockCli);
        else if (op == 2)
            SearchS0(recvsockCli);
        else if (op == 3)
            SearchUser1(recvsockCli);
        else if (op == 4)
            SearchUser2(recvsockCli);
        else if (op == 5)
            SearchT1(recvsockCli);
        else if (op == 6)
            SearchT2(recvsockCli);
        else if (op == 7)
            SearchNum(recvsockCli);
        else {
            strcpy(sendBuf, "\n������Ϸ��Ĳ���ѡ�\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }

        strcpy(sendBuf, "\n��ѡ����Ҫ��ѯ�����ݣ�\n1 - �����յ�\n2 - ��Ͷ�ݵ�\n3 - ��ѯ�ļ���\n4 - ��ѯ�ռ���\n5 - ��ѯ�ļ�ʱ��\n6 - ��ѯ�ռ�ʱ��\n7 - ��ѯ��ݵ���\n0 - �˳�\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "1");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
        op = atoi(recvBuf);
        cout << recvBuf;
        reLen = SOCKET_ERROR;
    }
}

void Courier::SearchS1(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchState1(this->m_username, recvsockCli);
}

void Courier::SearchS0(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchState0(this->m_username, recvsockCli);
}

void Courier::SearchUser1(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n��������Ҫ��ѯ�ļļ����û�����");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string username = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    Objects ob;
    ob.MyExpress(username, recvsockCli);
}

void Courier::SearchUser2(SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    int reLen = SOCKET_ERROR;

    strcpy(sendBuf, "\n��������Ҫ��ѯ���ռ����û�����");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    string username = recvBuf;
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    Objects ob;
    ob.MyReceive(username, recvsockCli);
}

void Courier::SearchT1(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchTime1(this->m_username, 3, recvsockCli);
}

void Courier::SearchT2(SOCKET recvsockCli) const {
    Objects ob;
    ob.SearchTime2(this->m_username, 3, recvsockCli);
}

void Courier::SearchNum(SOCKET recvsockCli) const{
    Objects ob;
    ob.SearchNumber(this->m_username, 3, recvsockCli);
}

void Courier::SaveInfo() const{
    ofstream write;
    write.open("./data/couriers.txt", ios::app);
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
    vector<string> t_remaining;//�˻����

    Info(t_username, t_name, t_phone, t_password, t_remaining);
    int number = 0;
    for (int i = 0; i < t_username.size(); i++) {
        if (this->m_username == t_username[i]) {
            number = i;
            break;
        }
    }
    //t_name[number] = this->m_name;
    //t_phone[number] = this->m_phone;
    //t_password[number] = this->m_password;
    stringstream ss;
    ss << this->m_remaining;
    t_remaining[number] = ss.str();

    ofstream change;
    change.open("./data/couriers.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("./data/couriers.txt", ios::app);
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