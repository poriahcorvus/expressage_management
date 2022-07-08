#include "Objects.h"
#include "public.h"

Objects::Objects() {
    this->m_number = "";//快递单号
    this->m_user1 = "";//寄件用户
    this->m_user2 = "";//收件用户
    this->m_state = -1;//物品状态：0-已签收， 1-待签收， 2-待揽收
    this->m_time1 = "";//寄送时间
    this->m_time2 = "";//接收时间
    this->m_cour = "";
    this->m_type = -1;//物品分类：1-易碎品， 2-图书， 3-普通快递
    this->m_weight = 0;
    this->m_description = "";//物品描述
}

Objects::~Objects() {}

/*
void Objects::SetObjects(){
    string number;//快递单号
    string user1;//寄件用户
    string user2;//收件用户
    int state;//物品状态：0-已签收， 1-待签收
    string time1;//寄送时间
    string time2;//接收时间
    string description;//物品描述

    cout << "快递单号：";
    cin >> number;
    this->m_number = number;

    cout << "寄件人：";
    cin >> user1;
    this->m_user1 = user1;
    cout << "收件人：";
    cin >> user2;
    this->m_user2 = user2;

    cout << "快递状态(0为已签收，1为待签收)：";
    cin >>state;
    this->m_state = state;

    cout << "寄送时间";
    cin >> time1;
    this->m_time1 = time1;
    if(state == 1){
        cout << "接收时间：暂无" << endl;
        time2 = "暂无";
    }
    else{
        cout << "接收时间：";
        cin >> time2;
    }
    this->m_time2 = time2;

    cout << "物品描述：";
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
    t += "年";
    t += month;
    t += "月";
    t += day;
    t += "日";
    t += hour;
    t += ":";
    t += min;

    return t;

}

void Objects::MyExpress(string username, SOCKET recvsockCli) const{
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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    char sendBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;
    cout << t_number.size();
    for (int i = 0; i < t_number.size(); i++) {
        if (t_user1[i] == username) {
            isin = 1;

            strcpy(sendBuf, "\n快递单号：");
            strcat(sendBuf, (char*)t_number[i].c_str());
            strcat(sendBuf, "\n收件人：");
            strcat(sendBuf, (char*)t_user2[i].c_str());
            strcat(sendBuf, "\n快递状态：");
            if (t_state[i] == 0)
                strcat(sendBuf, "已签收");
            else if (t_state[i] == 1)
                strcat(sendBuf, "待签收");
            else if (t_state[i] == 2)
                strcat(sendBuf, "待揽收");
            strcat(sendBuf, "\n发出时间：");
            strcat(sendBuf, (char*)t_time1[i].c_str());
            strcat(sendBuf, "\n签收时间：");
            strcat(sendBuf, (char*)t_time2[i].c_str());
            strcat(sendBuf, "\n快递员：");
            strcat(sendBuf, (char*)t_cour[i].c_str());
            strcat(sendBuf, "\n备注：");
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

    if (isin == 0) {
        strcpy(sendBuf, "\n无历史记录！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }

}

void Objects::MyReceive(string username, SOCKET recvsockCli) const {
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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    char sendBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_user2[i] == username) {
            isin = 1;

            strcpy(sendBuf, "\n快递单号：");
            strcat(sendBuf, (char*)t_number[i].c_str());
            strcat(sendBuf, "\n寄件人：");
            strcat(sendBuf, (char*)t_user1[i].c_str());
            strcat(sendBuf, "\n快递状态：");
            if (t_state[i] == 0)
                strcat(sendBuf, "已签收");
            else if (t_state[i] == 1)
                strcat(sendBuf, "待签收");
            else if (t_state[i] == 2)
                strcat(sendBuf, "待揽收");
            strcat(sendBuf, "\n发出时间：");
            strcat(sendBuf, (char*)t_time1[i].c_str());
            strcat(sendBuf, "\n签收时间：");
            strcat(sendBuf, (char*)t_time2[i].c_str());
            strcat(sendBuf, "\n快递员：");
            strcat(sendBuf, (char*)t_cour[i].c_str());
            strcat(sendBuf, "\n备注：");
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

    if (isin == 0) {
        strcpy(sendBuf, "\n无历史记录！\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }

}

void Objects::SearchNumber(string username, int identity, SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入所要查询的快递单号：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(sendBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;

    string number = recvBuf;

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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    if (identity == 2) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == number && (t_user1[i] == username || t_user2[i] == username)) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n快递员：");
                strcat(sendBuf, (char*)t_cour[i].c_str());
                strcat(sendBuf, "\n备注：");
                strcat(sendBuf, (char*)t_description[i].c_str());
                strcat(sendBuf, "\n");

                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "0");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                break;
            }
        }

        if (isin == 0) {
            strcpy(sendBuf, "\n这不是您的快递或快递不存在！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (identity == 3) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == number && t_cour[i] == username) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n备注：");
                strcat(sendBuf, (char*)t_description[i].c_str());
                strcat(sendBuf, "\n");

                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "0");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                break;
            }
        }

        if (isin == 0) {
            strcpy(sendBuf, "\n无历史记录！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (identity == 1) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == number) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n快递员：");
                strcat(sendBuf, (char*)t_cour[i].c_str());
                strcat(sendBuf, "\n备注：");
                strcat(sendBuf, (char*)t_description[i].c_str());
                strcat(sendBuf, "\n");

                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                cout << sendBuf;
                sLen = SOCKET_ERROR;

                strcpy(sendBuf, "0");
                sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
                sLen = SOCKET_ERROR;

                break;
            }
        }

        if (isin == 0) {
            strcpy(sendBuf, "\n无历史记录！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
}

void Objects::SearchTime1(string username, int identity, SOCKET recvsockCli) const {

    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入所要查询的快递发送时间：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(sendBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;
    string time1 = recvBuf;


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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    if (identity == 2) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_time1[i] == time1 && (t_user1[i] == username || t_user2[i] == username)) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n快递员：");
                strcat(sendBuf, (char*)t_cour[i].c_str());
                strcat(sendBuf, "\n备注：");
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

        if (isin == 0) {
            strcpy(sendBuf, "\n这不是您的快递或快递不存在！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (identity == 3) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_time1[i] == time1 && t_cour[i] == username) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n备注：");
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

        if (isin == 0) {
            strcpy(sendBuf, "\n无历史记录！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (identity == 1) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_time1[i] == time1) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n快递员：");
                strcat(sendBuf, (char*)t_cour[i].c_str());
                strcat(sendBuf, "\n备注：");
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

        if (isin == 0) {
            strcpy(sendBuf, "\n无历史记录！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }

}

void Objects::SearchTime2(string username, int identity, SOCKET recvsockCli) const {
    char sendBuf[SIZE] = {};
    char recvBuf[SIZE] = {};

    strcpy(sendBuf, "\n请输入所要查询的快递签收时间：");
    int sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    cout << sendBuf;
    sLen = SOCKET_ERROR;

    strcpy(sendBuf, "1");
    sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
    sLen = SOCKET_ERROR;

    int reLen = recv(recvsockCli, recvBuf, sizeof(sendBuf), 0);
    cout << recvBuf;
    reLen = SOCKET_ERROR;
    string time2 = recvBuf;

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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    if (identity == 2) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_time2[i] == time2 && (t_user1[i] == username || t_user2[i] == username)) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n寄件时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n收件时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n快递员：");
                strcat(sendBuf, (char*)t_cour[i].c_str());
                strcat(sendBuf, "\n备注：");
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

        if (isin == 0) {
            strcpy(sendBuf, "\n这不是您的快递或快递不存在！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (identity == 3) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_time2[i] == time2 && t_cour[i] == username) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n备注：");
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

        if (isin == 0) {
            strcpy(sendBuf, "\n无历史记录！\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
    else if (identity == 1) {
        for (int i = 0; i < t_number.size(); i++) {
            if (t_time2[i] == time2) {
                isin = 1;

                strcpy(sendBuf, "\n快递单号：");
                strcat(sendBuf, (char*)t_number[i].c_str());
                strcat(sendBuf, "\n寄件人：");
                strcat(sendBuf, (char*)t_user1[i].c_str());
                strcat(sendBuf, "\n收件人：");
                strcat(sendBuf, (char*)t_user2[i].c_str());
                strcat(sendBuf, "\n快递状态：");
                if (t_state[i] == 0)
                    strcat(sendBuf, "已签收");
                else if (t_state[i] == 1)
                    strcat(sendBuf, "待签收");
                else if (t_state[i] == 2)
                    strcat(sendBuf, "待揽收");
                strcat(sendBuf, "\n发出时间：");
                strcat(sendBuf, (char*)t_time1[i].c_str());
                strcat(sendBuf, "\n签收时间：");
                strcat(sendBuf, (char*)t_time2[i].c_str());
                strcat(sendBuf, "\n快递员：");
                strcat(sendBuf, (char*)t_cour[i].c_str());
                strcat(sendBuf, "\n备注：");
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

        if (isin == 0) {
            strcpy(sendBuf, "\n无历史记录\n");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            cout << sendBuf;
            sLen = SOCKET_ERROR;

            strcpy(sendBuf, "0");
            sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
            sLen = SOCKET_ERROR;
        }
    }
}

void Objects::SearchState0(string username, SOCKET recvsockCli) const {
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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    char sendBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_cour[i] == username && t_state[i] == 0) {
            isin = 1;

            strcpy(sendBuf, "快递单号：");
            strcat(sendBuf, t_number[i].c_str());
            strcat(sendBuf, "\n寄件人：");
            strcat(sendBuf, t_user1[i].c_str());
            strcat(sendBuf, "\n收件人：");
            strcat(sendBuf, t_user2[i].c_str());
            strcat(sendBuf, "\n发出时间：");
            strcat(sendBuf, t_time1[i].c_str());
            strcat(sendBuf, "\n签收时间：");
            strcat(sendBuf, t_time2[i].c_str());
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

    if (isin == 0) {
        strcpy(sendBuf, "\n无历史记录\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }
}

void Objects::SearchState1(string username, SOCKET recvsockCli) const {
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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;
    char sendBuf[SIZE] = {};
    int sLen = SOCKET_ERROR;

    for (int i = 0; i < t_number.size(); i++) {
        if (t_cour[i] == username && t_state[i] == 1) {
            isin = 1;

            strcpy(sendBuf, "快递单号：");
            strcat(sendBuf, t_number[i].c_str());
            strcat(sendBuf, "\n寄件人：");
            strcat(sendBuf, t_user1[i].c_str());
            strcat(sendBuf, "\n收件人：");
            strcat(sendBuf, t_user2[i].c_str());
            strcat(sendBuf, "\n发出时间：");
            strcat(sendBuf, t_time1[i].c_str());
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

    if (isin == 0) {
        strcpy(sendBuf, "\n无历史记录\n");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        cout << sendBuf;
        sLen = SOCKET_ERROR;

        strcpy(sendBuf, "0");
        sLen = send(recvsockCli, sendBuf, sizeof(sendBuf), 0);
        sLen = SOCKET_ERROR;
    }
}

void Objects::SaveObjects() const {
    ofstream write;
    write.open("./data/objects.txt", ios::app);
    if (!write.is_open()) {
        cout << "快递信息保存失败！" << endl;
        return;
    }
    write << this->m_number << ' '
        << this->m_user1 << ' '
        << this->m_user2 << ' '
        << this->m_state << ' '
        << this->m_time1 << ' '
        << this->m_time2 << ' '
        << this->m_cour << ' '
        << this->m_type << ' '
        << this->m_weight << ' '
        << this->m_description
        << endl;
    //cout << "快递信息保存成功！" << endl;
}

void Objects::UpdateObjects() const {
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
    ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);
    int index = 0;
    for (int i = 0; i < t_number.size(); i++) {
        if (this->m_number == t_number[i]) {
            index = i;
            break;
        }
    }
    t_state[index] = this->m_state;
    t_time2[index] = this->m_time2;
    t_cour[index] = this->m_cour;

    ofstream change;
    change.open("./data/objects.txt", ios::trunc | ios::out);
    change.close();
    ofstream write;
    write.open("./data/objects.txt", ios::app);
    if (!write.is_open()) {
        cout << "快递信息更新失败！" << endl;
        return;
    }
    for (int i = 0; i < t_number.size(); i++) {
        write << t_number[i] << ' '
            << t_user1[i] << ' '
            << t_user2[i] << ' '
            << t_state[i] << ' '
            << t_time1[i] << ' '
            << t_time2[i] << ' '
            << t_cour[i] << ' '
            << t_type[i] << ' '
            << t_weight[i] << ' '
            << t_description[i]
            << endl;
    }
    write.close();
}

void Objects::ShowObjects(vector<string>& t_number, vector<string>& t_user1, vector<string>& t_user2, vector<int>& t_state, vector<string>& t_time1, vector<string>& t_time2, vector<string>& t_cour, vector<int>& t_type, vector<string>& t_weight, vector<string>& t_description) const {
    ifstream fl;
    fl.open("./data/objects.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取快递信息失败" << endl;
        return;
    }
    string t1 = "";//单号
    string t2 = "";//寄件人
    string t3 = "";//收件人
    int t4 = -1;//快递状态
    string t5 = "";//寄送时间
    string t6 = "";//签收时间
    string t7 = "";//快递员
    int t8 = -1;//快递分类
    string t9 = "";//快递重量
    string t10 = "";//备注
    for (int i = 0; i < CountObjects(); i++) {
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

        t_number.push_back(t1);
        t_user1.push_back(t2);
        t_user2.push_back(t3);
        t_state.push_back(t4);
        t_time1.push_back(t5);
        t_time2.push_back(t6);
        t_cour.push_back(t7);
        t_type.push_back(t8);
        t_weight.push_back(t9);
        t_description.push_back(t10);

        t1 = "";
        t2 = "";
        t3 = "";
        t4 = -1;
        t5 = "";
        t6 = "";
        t7 = "";
        t8 = -1;
        t9 = "";
        t10 = "";
    }
    fl.close();
}

int Objects::CountObjects() const {
    ifstream fl;
    fl.open("./data/objects.txt", ios::in);
    if (!fl.is_open()) {
        cout << "读取快递数失败" << endl;
        return -1;
    }

    int count = 0;
    char temp[1024] = {};
    while (!fl.eof()) {
        fl.getline(temp, 1024);
        count++;
    }
    fl.close();
    count--;
    return count;
}