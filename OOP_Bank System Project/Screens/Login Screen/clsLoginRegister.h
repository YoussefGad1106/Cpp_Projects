#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsDate.h"
#include "clsGlobal.h"
#include "clsScreen.h"
#include "clsBankUser.h"

using namespace std;

class clsLoginRegister : protected clsScreen
{
private :

    static void _PrintLoginRecordLine(clsBankUser::stLoginRegisterData User)
    {
        cout << "\t| " << setw(30) << left << User.LoginTime;
        cout << "\t| " << setw(10) << left << User.UserName;
        cout << "\t| " << setw(15) << left << User.UserPassword;
        cout << "\t| " << setw(12) << left << User.Permissions;
    }

    static clsBankUser::stLoginRegisterData _ConvertLineToUserObject(string Line, string Separator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Separator);
        clsBankUser::stLoginRegisterData LoginRegisterData;

        LoginRegisterData.LoginTime = vUserData[0];
        LoginRegisterData.UserName = vUserData[1];
        LoginRegisterData.UserPassword = vUserData[2];
        LoginRegisterData.Permissions = stoi(vUserData[3]);

        return LoginRegisterData;
    }
	
    static vector<clsBankUser::stLoginRegisterData> _LoadLoggedInUsersDataFromFile()
    {
        fstream MyFile;
        string Line;
        vector<clsBankUser::stLoginRegisterData> vUsers;

        MyFile.open("Login Register.txt", ios::in);

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                vUsers.push_back(_ConvertLineToUserObject(Line));
            }
        }

        MyFile.close();
        return vUsers;
    }

public :

    static void ShowLoginRegisterScreen()
    {
        if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enLoginRegister))
        {
            return;
        }
        vector <clsBankUser::stLoginRegisterData> vUsers = _LoadLoggedInUsersDataFromFile();

        _DrawScreenHeader("Login Register Menu", to_string(vUsers.size()) + " Login(s).");
        cout << "\n\t_______________________________________________";
        cout << "_________________________________________________\n" << endl;

        cout << "\t| " << left << setw(30) << "Date/Time";
        cout << "\t| " << left << setw(10) << "UserName";
        cout << "\t| " << left << setw(15) << "User Password";
        cout << "\t| " << left << setw(12) << "Permissions";
        cout << "\n\t_______________________________________________";
        cout << "_________________________________________________\n" << endl;

        if (vUsers.empty())
            cout << "\t\t\t  No Previous Logins History!!";
        else

            for (clsBankUser::stLoginRegisterData User : vUsers)
            {

                _PrintLoginRecordLine(User);
                cout << endl;
            }

        cout << "\n\t_______________________________________________";
        cout << "_________________________________________________\n" << endl;
    }
};

