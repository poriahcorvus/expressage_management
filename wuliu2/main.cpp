#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>

#include "Manager.h"
#include "Courier.h"
#include "Users.h"
#include "Fragile.h"
#include "Book.h"
#include "Ordinary.h"

using namespace std;

int main()
{
    int identity;
    int choice;

    cout << "\n��ӭʹ����������ϵͳ��\n" << endl;

    cout << "��ѡ��������ݣ�" << endl;
    cout << "1 - ����Ա\n2 - ��ͨ�û�\n3 - ���Ա\n0 - �˳�" << endl;
    cin >> identity;

    if (identity)
        cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
    if (identity == 1) {
        cout << "1 - ��¼\n0 - �˳�" << endl;
        cin >> choice;

        if (choice == 1) {
            Manager manager;
            int op1;
            int l = manager.LogIn2();
            if (l == 1) {
                cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                cout << "1 - ��ѯ\n2 - ������Ա\n3 - Ϊ���ָ�ɿ��Ա\n0 - �˳�" << endl;
                cin >> op1;
                while (op1) {

                    switch (op1) {
                    case 1:     manager.SearchInfo();   break;
                    case 2:     manager.ManageCour();   break;
                    case 3:     manager.AllotCour();    break;
                    case 0:     break;
                    default:    cout << "\n������Ϸ��Ĳ�����\n" << endl;
                    }

                    cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                    cout << "1 - ��ѯ\n2 - ������Ա\n3 - Ϊ���ָ�ɿ��Ա\n0 - �˳�" << endl;
                    cin >> op1;

                }
            }
        }
    }
    if (identity == 2) {
        cout << "1 - ��¼\n2 - ���û�ע��\n0 - �˳�" << endl;
        cin >> choice;

        if (choice == 1 || choice == 2) {
            Users user;
            if (choice == 2)
                user.SignUp();

            int op2;
            int l = user.LogIn1();
            if (l == 1) {
                cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                cout << "1 - �޸�����\n2 - ��ѯ�˻����\n3 - �˻���ֵ\n4 - �ļ�\n5 - ȡ��\n6 - ��ѯ���\n0 - �˳�" << endl;
                cin >> op2;
                while (op2) {

                    switch (op2) {
                    case 1:     user.ChangePass();      break;
                    case 2:     user.CheckRemain();     break;
                    case 3:     user.TopUp();           break;
                    case 4:     user.ExpressDel();      break;
                    case 5:     user.ReceiveDel();      break;
                    case 6:     user.SearchDel();       break;
                    case 0:     break;
                    default:    cout << "\n������Ϸ�������\n" << endl;
                    }

                    cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                    cout << "1 - �޸�����\n2 - ��ѯ�˻����\n3 - �˻���ֵ\n4 - �ļ�\n5 - ȡ��\n6 - ��ѯ���\n0 - �˳�" << endl;
                    cin >> op2;

                }
            }
        }
    }
    if (identity == 3) {
        cout << "1 - ��¼\n0 - �˳�" << endl;
        cin >> choice;

        if (choice == 1) {
            Courier courier;
            int op3;
            int l = courier.LogIn3();
            if (l == 1) {
                cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                cout << "1 - ���տ��\n2 - ��ѯ\n0 - �˳�" << endl;
                cin >> op3;
                while (op3) {

                    switch (op3) {
                    case 1:     courier.SendDel();      break;
                    case 2:     courier.SearchDel();    break;
                    case 0:     break;
                    default:    cout << "\n������Ϸ�������\n" << endl;
                    }

                    cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                    cout << "1 - ���տ��\n2 - ��ѯ\n0 - �˳�" << endl;
                    cin >> op3;
                }
            }
        }
    }
}