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

    cout << "\n欢迎使用物流管理系统！\n" << endl;
    cout << "请选择您的身份：" << endl;
    cout << "1 - 管理员\n2 - 普通用户\n0 - 退出" << endl;
    cin >> identity;
    cout << "\n请选择接下来要执行的操作：" << endl;
    if (identity == 1) {
        cout << "1 - 登录\n0 - 退出" << endl;
        cin >> choice;
        if (choice == 1) {
            Manager manager;
            int op1;
            if (manager.LogIn2() == 1) {
                cout << "\n请选择接下来要执行的操作：" << endl;
                cout << "1 - 查看所有用户信息\n2 - 查看所有快递信息\n3 - 查询\n0 - 退出" << endl;
                cin >> op1;
                switch (op1) {
                case 1:     manager.UsInfo();       break;
                case 2:     manager.ObInfo();       break;
                case 3:     manager.SearchInfo();   break;
                case 0:     break;
                default:    cout << "\n请输入合法的操作！\n" << endl;
                }
                while (op1) {
                    cout << "\n请选择接下来要执行的操作：" << endl;
                    cout << "1 - 查看所有用户信息\n2 - 查看所有快递信息\n3 - 查询\n0 - 退出" << endl;
                    cin >> op1;
                    switch (op1) {
                    case 1:     manager.UsInfo();       break;
                    case 2:     manager.ObInfo();       break;
                    case 3:     manager.SearchInfo();   break;
                    case 0:     break;
                    default:    cout << "\n请输入合法的操作！\n" << endl;
                    }
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
            if (user.LogIn1() == 1) {
                cout << "\n请选择接下来要执行的操作：" << endl;
                cout << "1 - 修改密码\n2 - 查询账户余额\n3 - 账户充值\n4 - 寄件\n5 - 取件\n6 - 查询快递\n0 - 退出" << endl;
                cin >> op2;
                switch (op2) {
                case 1:     user.ChangePass();      break;
                case 2:     user.CheckRemain();     break;
                case 3:     user.TopUp();           break;
                case 4:     user.ExpressDel();      break;
                case 5:     user.ReceiveDel();      break;
                case 6:     user.SearchDel();       break;
                case 0:     break;
                default:    cout << "\n请输入合法的操作！\n" << endl;
                }
                while (op2) {
                    cout << "\n请选择接下来要执行的操作：" << endl;
                    cout << "1 - 修改密码\n2 - 查询账户余额\n3 - 账户充值\n4 - 寄件\n5 - 取件\n6 - 查询快递\n0 - 退出" << endl;
                    cin >> op2;
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
                }
            }
        }
    }
}