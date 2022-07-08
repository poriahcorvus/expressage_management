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

    cout << "\n欢迎使用物流管理系统！\n" << endl;

    cout << "请选择您的身份：" << endl;
    cout << "1 - 管理员\n2 - 普通用户\n3 - 快递员\n0 - 退出" << endl;
    cin >> identity;

    if (identity)
        cout << "\n请选择接下来要执行的操作：" << endl;
    if (identity == 1) {
        cout << "1 - 登录\n0 - 退出" << endl;
        cin >> choice;

        if (choice == 1) {
            Manager manager;
            int op1;
            int l = manager.LogIn2();
            if (l == 1) {
                cout << "\n请选择接下来要执行的操作：" << endl;
                cout << "1 - 查询\n2 - 管理快递员\n3 - 为快递指派快递员\n0 - 退出" << endl;
                cin >> op1;
                while (op1) {

                    switch (op1) {
                    case 1:     manager.SearchInfo();   break;
                    case 2:     manager.ManageCour();   break;
                    case 3:     manager.AllotCour();    break;
                    case 0:     break;
                    default:    cout << "\n请输入合法的操作！\n" << endl;
                    }

                    cout << "\n请选择接下来要执行的操作：" << endl;
                    cout << "1 - 查询\n2 - 管理快递员\n3 - 为快递指派快递员\n0 - 退出" << endl;
                    cin >> op1;

                }
            }
        }
    }
    if (identity == 2) {
        cout << "1 - 登录\n2 - 新用户注册\n0 - 退出" << endl;
        cin >> choice;

        if (choice == 1 || choice == 2) {
            Users user;
            if (choice == 2)
                user.SignUp();

            int op2;
            int l = user.LogIn1();
            if (l == 1) {
                cout << "\n请选择接下来要执行的操作：" << endl;
                cout << "1 - 修改密码\n2 - 查询账户余额\n3 - 账户充值\n4 - 寄件\n5 - 取件\n6 - 查询快递\n0 - 退出" << endl;
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
                    default:    cout << "\n请输入合法操作！\n" << endl;
                    }

                    cout << "\n请选择接下来要执行的操作：" << endl;
                    cout << "1 - 修改密码\n2 - 查询账户余额\n3 - 账户充值\n4 - 寄件\n5 - 取件\n6 - 查询快递\n0 - 退出" << endl;
                    cin >> op2;

                }
            }
        }
    }
    if (identity == 3) {
        cout << "1 - 登录\n0 - 退出" << endl;
        cin >> choice;

        if (choice == 1) {
            Courier courier;
            int op3;
            int l = courier.LogIn3();
            if (l == 1) {
                cout << "\n请选择接下来要执行的操作：" << endl;
                cout << "1 - 揽收快递\n2 - 查询\n0 - 退出" << endl;
                cin >> op3;
                while (op3) {

                    switch (op3) {
                    case 1:     courier.SendDel();      break;
                    case 2:     courier.SearchDel();    break;
                    case 0:     break;
                    default:    cout << "\n请输入合法操作！\n" << endl;
                    }

                    cout << "\n请选择接下来要执行的操作：" << endl;
                    cout << "1 - 揽收快递\n2 - 查询\n0 - 退出" << endl;
                    cin >> op3;
                }
            }
        }
    }
}