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

int main()
{
    int identity;
    int choice;

    cout << "\n��ӭʹ����������ϵͳ��\n" << endl;
    cout << "��ѡ��������ݣ�" << endl;
    cout << "1 - ����Ա\n2 - ��ͨ�û�\n0 - �˳�" << endl;
    cin >> identity;
    cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
    if (identity == 1) {
        cout << "1 - ��¼\n0 - �˳�" << endl;
        cin >> choice;
        if (choice == 1) {
            Manager manager;
            int op1;
            if (manager.LogIn2() == 1) {
                cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                cout << "1 - �鿴�����û���Ϣ\n2 - �鿴���п����Ϣ\n3 - ��ѯ\n0 - �˳�" << endl;
                cin >> op1;
                switch (op1) {
                case 1:     manager.UsInfo();       break;
                case 2:     manager.ObInfo();       break;
                case 3:     manager.SearchInfo();   break;
                case 0:     break;
                default:    cout << "\n������Ϸ��Ĳ�����\n" << endl;
                }
                while (op1) {
                    cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                    cout << "1 - �鿴�����û���Ϣ\n2 - �鿴���п����Ϣ\n3 - ��ѯ\n0 - �˳�" << endl;
                    cin >> op1;
                    switch (op1) {
                    case 1:     manager.UsInfo();       break;
                    case 2:     manager.ObInfo();       break;
                    case 3:     manager.SearchInfo();   break;
                    case 0:     break;
                    default:    cout << "\n������Ϸ��Ĳ�����\n" << endl;
                    }
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
            if (user.LogIn1() == 1) {
                cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                cout << "1 - �޸�����\n2 - ��ѯ�˻����\n3 - �˻���ֵ\n4 - �ļ�\n5 - ȡ��\n6 - ��ѯ���\n0 - �˳�" << endl;
                cin >> op2;
                switch (op2) {
                case 1:     user.ChangePass();      break;
                case 2:     user.CheckRemain();     break;
                case 3:     user.TopUp();           break;
                case 4:     user.ExpressDel();      break;
                case 5:     user.ReceiveDel();      break;
                case 6:     user.SearchDel();       break;
                case 0:     break;
                default:    cout << "\n������Ϸ��Ĳ�����\n" << endl;
                }
                while (op2) {
                    cout << "\n��ѡ�������Ҫִ�еĲ�����" << endl;
                    cout << "1 - �޸�����\n2 - ��ѯ�˻����\n3 - �˻���ֵ\n4 - �ļ�\n5 - ȡ��\n6 - ��ѯ���\n0 - �˳�" << endl;
                    cin >> op2;
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
                }
            }
        }
    }
}