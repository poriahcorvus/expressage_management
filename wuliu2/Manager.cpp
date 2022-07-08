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
    int t8 = -1;
    double t9 = 0;
    string t10 = "";

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
        fl >> t8;
        fl >> t9;
        fl >> t10;

        cout << "\n��ݵ��ţ�" << t1
            << "\n�ļ��ˣ�" << t2
            << "\n�ռ��ˣ�" << t3
            << "\n���״̬��";
        if (t4 == 0)
            cout << "��ǩ��";
        else if (t4 == 1)
            cout << "��ǩ��";
        else if (t4 == 2)
            cout << "������";
        cout << "\n�ļ�ʱ�䣺" << t5
            << "\n�ռ�ʱ�䣺" << t6
            << "\n���Ա��" << t7
            << "\n��Ʒ���ࣺ";
        if (t8 == 1)
            cout << "����Ʒ";
        else if (t8 == 2)
            cout << "ͼ��";
        else if (t8 == 3)
            cout << "��ͨ���";
        cout << "\n���������" << t9
            << "\n���������" << t10
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
    cout << "\n�����ڲ鿴���п��Ա��Ϣ��\n" << endl;

    ifstream fl;
    fl.open("couriers.txt", ios::in);
    if (!fl.is_open()) {
        cout << "�鿴���Ա��Ϣʧ�ܣ�" << endl;
        return;
    }
    string t1 = "";
    string t2 = "";
    string t3 = "";
    string t4 = "";//���벻��ʾ
    double t5 = 0;
    Courier courier;
    int number = courier.Count();
    cout << "���Ա����" << number << '\n' << endl;
    for (int i = 0; i < number; i++) {
        fl >> t1;
        fl >> t2;
        fl >> t3;
        fl >> t4;
        fl >> t5;

        cout << "�û�����" << t1
            << "\n������" << t2
            << "\n��ϵ��ʽ��" << t3
            << "\n�˻���" << t5
            << '\n' << endl;


        t1 = "";
        t2 = "";
        t3 = "";
        t4 = "";//���벻��ʾ
        t5 = 0;
    }
    fl.close();
}

void Manager::SearchInfo() const {

    cout << "\n��ѡ����Ҫ��ѯ�����ݣ�\n" << endl;
    cout << "\n1 - �����û�\n2 - ���п��\n3 - ���п��Ա\n\n"
        << "4 - ��ͨ�û�\n5 - �ļ���\n6 - �ռ���\n7 - �ļ�ʱ��\n8 - �ռ�ʱ��\n"
        << "9 - ���Ա\n10 - ��ݵ���\n0 - �˳�"
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
        default:    cout << "������Ϸ��Ĳ���ѡ�" << endl;
        }

        cout << "\n�����ѡ����Ҫ��ѯ�����ݣ�\n" << endl;
        cout << "\n1 - �����û�\n2 - ���п��\n3 - ���п��Ա\n\n"
            << "4 - ��ͨ�û�\n5 - �ļ���\n6 - �ռ���\n7 - �ļ�ʱ��\n8 - �ռ�ʱ��\n"
            << "9 - ���Ա\n10 - ��ݵ���\n0 - �˳�"
            << endl;
        cin >> op;
    }
}

void Manager::SearchUser() const {
    cout << "\n��������Ҫ��ѯ���û�����";
    Users user;
    string username;
    cin >> username;

    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����
    vector<string> t_address;//��ַ

    user.Info(t_username, t_name, t_phone, t_password, t_remaining, t_address);
    int number = -1;
    for (int i = 0; i < t_username.size(); i++) {
        if (username == t_username[i]) {
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
    obj.MyExpress(username);


    cout << "\n���û��յ��İ�����" << endl;
    obj.MyReceive(username);


}

void Manager::SearchExpress() const {
    cout << "��������Ҫ��ѯ�ļļ����û�����";
    string username = "";
    cin >> username;

    Objects ob;
    ob.MyExpress(username);
}

void Manager::SearchReceive() const {
    cout << "��������Ҫ��ѯ���ռ����û�����";
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
    cout << "������Ҫ��ѯ�Ŀ��Ա�û�����";
    string username;
    cin >> username;


    Courier courier;
    Objects ob;
    int index = 0;
    int isin = 0;
    vector<string> t_username;//�û���
    vector<string> t_name;//����
    vector<string> t_phone;//�绰
    vector<string> t_password;//����
    vector<double> t_remaining;//�˻����
    courier.Info(t_username, t_name, t_phone, t_password, t_remaining);
    for (int i = 0; i < t_username.size(); i++) {
        if (t_username[i] == username) {
            index = i;
            isin = 1;
            break;
        }
    }

    if (isin == 0) {
        cout << "\n��������ȷ�Ŀ��Ա�û�����\n" << endl;
        return;
    }

    cout << "\n�û�����" << t_username[index]
        << "\n������" << t_name[index]
        << "\n��ϵ��ʽ��" << t_phone[index]
        << "\n���룺" << t_remaining[index]
        << endl;

    cout << "\n�ÿ��Ա�����յĿ�ݣ�" << endl;
    ob.SearchState1(username);

    cout << "\n�ÿ��Ա�����͵Ŀ�ݣ�" << endl;
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
    cout << "\n��������Ҫ��ѯ�Ŀ�ݵ��ţ�";
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
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if(t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if(t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << endl;
            break;
        }
    }

    if(isin == 0)
        cout << "\n��ݲ����ڣ�\n" << endl;
}

void Manager::SearchTime_1(){
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
    vector<string> t_cour;
    vector<int> t_type;
    vector<double> t_weight;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;

    for(int i = 0; i < t_number.size(); i ++){
        if(t_time1[i] == time1){
            isin = 1;
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if(t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if(t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << endl;
        }
    }

    if(isin == 0)
        cout << "\n����ʷ��¼��\n" << endl;

}

void Manager::SearchTime_2(){
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
    vector<string> t_cour;
    vector<int> t_type;
    vector<double> t_weight;
    vector<string> t_description;
    obj.ShowObjects(t_number, t_user1, t_user2, t_state, t_time1, t_time2, t_cour, t_type, t_weight, t_description);

    int isin = 0;

    for(int i = 0; i < t_number.size(); i ++){
        if(t_time2[i] == time2){
            isin = 1;
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i];
            if(t_state[i] == 0)
                cout << "\n���״̬����ǩ��";
            else if(t_state[i] == 1)
                cout << "\n���״̬��������";
            cout << "\n����ʱ�䣺" << t_time1[i]
                << "\nǩ��ʱ�䣺" << t_time2[i]
                << "\n��ע��" << t_description[i]
                << endl;
        }
    }

    if(isin == 0)
        cout << "\n����ʷ��¼��\n" << endl;

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

    t_remaining = t_remaining + price;

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

void Manager::ManageCour() const {
    int choice;
    cout << "��ѡ��\n1 - ��ӿ��Ա\n2 - ɾ�����Ա\n0 - �˳�����" << endl;
    cin >> choice;

    while (choice) {
        Courier courier;
        if (choice == 1)
            courier.SetCourier();
        else if (choice == 2)
            courier.RemoveCourier();
        cout << "\n��ѡ��\n1 - ��ӿ��Ա\n2 - ɾ�����Ա\n0 - �˳�����" << endl;
        cin >> choice;

    }
}

void Manager::AllotCour() const {
    cout << "\n������ָ�ɿ��Ա��" << endl;

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
        if (t_state[i] == 2 && t_cour[i] == "����") {
            isex += 1;
            cout << "\n��ݵ��ţ�" << t_number[i]
                << "\n�ļ��ˣ�" << t_user1[i]
                << "\n�ռ��ˣ�" << t_user2[i]
                << "\n��ݷ��ࣺ";
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
        cout << "\n���п�ݶ��Ѿ�ָ�ɿ��Ա��" << endl;
        return;
    }
    cout << "\n������Ҫָ�ɵĿ�ݵ��ţ�";
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

            cout << "\n������Ҫָ�ɵĿ��Ա��";
            cin >> co;

            ob.m_cour = co;
            ob.m_state = t_state[i];
            ob.m_time2 = t_time2[i];
            ob.UpdateObjects();

            cout << "\nָ�ɳɹ���" << endl;;
            break;
        }
    }

    if (isin == 0) {
        cout << "\n��������ȷ�Ŀ�ݵ��ţ�" << endl;
    }

    if (isex == 0) {
        cout << "\n���п�ݶ��Ѿ�ָ�ɿ��Ա��" << endl;
        return;
    }

    cout << "\n�Ƿ����ָ�ɿ��Ա��\n1 - ����\t0 - �˳�" << endl;
    int iscon = 0;
    cin >> iscon;

    while (iscon == 1) {
        se = "";
        co = "";
        isin = 0;

        cout << "\n������Ҫָ�ɵĿ�ݵ��ţ�";
        cin >> se;

        for (int i = 0; i < t_number.size(); i++) {
            if (t_number[i] == se) {
                isin = 1;
                isex -= 1;

                Objects ob;
                ob.m_number = se;

                cout << "\n������Ҫָ�ɵĿ��Ա��";
                cin >> co;

                ob.m_cour = co;
                ob.m_state = t_state[i];
                ob.m_time2 = t_time2[i];
                ob.UpdateObjects();

                cout << "\nָ�ɳɹ���" << endl;;
                break;
            }
        }
        if (isin == 0) {
            cout << "\n��������ȷ�Ŀ�ݵ��ţ�" << endl;
        }

        if (isex == 0) {
            cout << "\n���п�ݶ��Ѿ�ָ�ɿ��Ա��" << endl;
            return;
        }

        cout << "\n�Ƿ����ָ�ɿ��Ա��\n1 - ����\t0 - �˳�" << endl;
        cin >> iscon;
    }
}