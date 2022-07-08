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

    strcpy(sendBuf, "\n�û�����");
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
        this->m_remaining = stod(t_remaining[i]);
        this->m_address = t_address[i];

        strcpy(sendBuf, "\n��½�ɹ���\n");
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

void Users::SignUp(SOCKET recvsockCli) {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n������һ���û�����");
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
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<string> t_remaining;//�˻����
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
        strcpy(sendBuf, "\n�û����Ѵ��ڣ�\n������һ���û�����");
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

    strcpy(sendBuf, "\n���������룺");
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

    strcpy(sendBuf, "\n��ȷ�����룺");
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
        strcpy(sendBuf, "\n�������벻һ��\n������ȷ�����룺");
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

    strcpy(sendBuf, "\nע��ɹ���\n���������ĸ�����Ϣ��");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    SetMess(recvsockCli);
    SaveInfo(recvsockCli);

    strcpy(sendBuf, "\n�����µ�¼����֤��ݣ�\n");
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

    strcpy(sendBuf, "\n����������");
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

    strcpy(sendBuf, "\n�����ֻ��ţ�");
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

    strcpy(sendBuf, "\n���ĵ�ַ��");
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

    strcpy(sendBuf, "\n�������޸����룡\n�����������룺");
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

    strcpy(sendBuf, "\n��ȷ�������룺");
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
        strcpy(sendBuf, "\n�������벻һ��\n������ȷ�����룺");
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

    strcpy(sendBuf, "\n�����޸ĳɹ���\n");
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

    strcpy(sendBuf, "\n�����ڲ�ѯ�˻����!\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    stringstream ss;
    ss << this->m_remaining;
    string s = ss.str();
    strcpy(sendBuf, "�����˻����Ϊ��");
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

    strcpy(sendBuf, "\n��������Ҫ��ֵ�Ľ���������");
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

    strcpy(sendBuf, "\n��ֵ�ɹ���\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    stringstream ss;
    ss << this->m_remaining;
    string s = ss.str();
    strcpy(sendBuf, "\n�����˻����Ϊ��");
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

    strcpy(sendBuf, "\n���������뷢�Ϳ��\n\n��ѡ������Ʒ���ࣺ\n1 - ����Ʒ\t2 - ͼ��\t3 - ��ͨ��Ʒ\n");
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
            strcpy(sendBuf, "\n����Ѵ�������ڵȴ����գ�\n");
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
            strcpy(sendBuf, "\n���㣬���ֵ��\n");
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
            strcpy(sendBuf, "\n����Ѵ�������ڵȴ����գ�\n");
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
            strcpy(sendBuf, "\n���㣬���ֵ��\n");
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
            strcpy(sendBuf, "\n����Ѵ�������ڵȴ����գ�\n");
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
            strcpy(sendBuf, "\n���㣬���ֵ��\n");
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

    strcpy(sendBuf, "\n�������ռ����û�����");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    reLen = recv(recvsockCli, recvBuf, sizeof(recvBuf), 0);
    cout << recvBuf;
    ob.m_user2 = recvBuf;
    ob.m_state = 2;//0-��ǩ�գ�1-��ǩ�գ� 2-������
    ob.m_time1 = ob.GetTime();
    ob.m_time2 = "����";
    ob.m_cour = "����";

    strcpy(sendBuf, "\n��������������");
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

    strcpy(sendBuf, "\n�������ݱ�ע��");
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

    strcpy(sendBuf, "\n������ǩ�տ�ݣ�\n");
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
            strcpy(sendBuf, "\n��ݵ��ţ�");
            strcat(sendBuf, t_number[i].c_str());
            strcat(sendBuf, "\n�ļ��ˣ�");
            strcat(sendBuf, t_user1[i].c_str());
            strcat(sendBuf, "\n��Ʒ���");
            if (t_type[i] == 1)
                strcat(sendBuf, "����Ʒ");
            else if (t_type[i] == 2)
                strcat(sendBuf, "ͼ��");
            else if (t_type[i] == 3)
                strcat(sendBuf, "��ͨ��Ʒ");
            strcat(sendBuf, "\n��ע��");
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
        strcpy(sendBuf, "\n��û�д�ǩ�յĿ�ݣ�\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;

        return;
    }

    strcpy(sendBuf, "\n��ѡ��Ҫǩ�յĿ�ݣ����뵥�ţ���");
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

            strcpy(sendBuf, "\nǩ�ճɹ���\n");
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
        strcpy(sendBuf, "\n�Ƿ����ǩ�տ�ݣ�\n1 - ����ǩ�տ��\t0 - �˳�\n");
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

            strcpy(sendBuf, "\n��ѡ��Ҫǩ�յĿ�ݣ����뵥�ţ���");
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

                    strcpy(sendBuf, "\nǩ�ճɹ���\n");
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
                strcpy(sendBuf, "\n�Ƿ����ǩ�տ�ݣ�\n1 - ����ǩ�տ��\t0 - �˳�\n");
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
                strcpy(sendBuf, "\n��û�д�ǩ�յĿ�ݣ�\n");
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
        strcpy(sendBuf, "\n��û�д�ǩ�յĿ�ݣ�\n");
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

    strcpy(sendBuf, "\n��ѡ����Ҫ��ѯ�����ݣ�\n1 - �Ҽĳ���\n2 - ���յ���\n3 - ��ѯ��ݵ���\n4 - ��ѯ����ʱ��\n5 - ��ѯǩ��ʱ��\n0 - �˳���ѯ\n");
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
            strcpy(sendBuf, "\n������Ϸ��Ĳ�����\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }

        strcpy(sendBuf, "\n��ѡ����Ҫ��ѯ�����ݣ�\n1 - �Ҽĳ���\n2 - ���յ���\n3 - ��ѯ��ݵ���\n4 - ��ѯ����ʱ��\n5 - ��ѯǩ��ʱ��\n0 - �˳���ѯ\n");
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

void Users::Info(vector<string>& t_username, vector<string>& t_name, vector<string>& t_phone, vector<string>& t_password, vector<string>& t_remaining, vector<string>& t_address) const {
    ifstream fl;
    fl.open("./data/users.txt", ios::in);
    if (!fl.is_open()) {
        cout << "��ȡ�û���ʧ��" << endl;
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
    strcpy(sendBuf, "\n��Ϣ����ɹ���\n");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "0");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;
}

void Users::UpdateInfo() const {
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<string> t_remaining;//�˻����
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