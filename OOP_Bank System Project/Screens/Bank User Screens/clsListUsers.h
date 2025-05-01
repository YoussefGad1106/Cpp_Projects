#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsBankUser.h"
#include "clsScreen.h"

using namespace std;

class clsListUsers : protected clsScreen
{

private:

    static void _PrintUserRecordLine(clsBankUser User)
    {

        cout << "| " << setw(10) << left << User.GetUserName();
        cout << "| " << setw(20) << left << User.GetFullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(25) << left << User.Email;
        cout << "| " << setw(15) << left << User.UserPassword;
        cout << "| " << setw(12) << left << User.Permissions;

    }
public:

    static void ShowUsersList()
    {

        vector <clsBankUser> vUsers = clsBankUser::GetUsersList();

        _DrawScreenHeader("Users List", to_string(vUsers.size()) + " User(s).");
        cout << "\n_______________________________________________________";
        cout << "___________________________________________________________\n" << endl;

        cout << "| " << left << setw(10) << "UserName";
        cout << "| " << left << setw(20) << "Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(15) << "User Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "___________________________________________________________\n" << endl;

        if (vUsers.empty())
            cout << "\t\t\t  No Users Available In the System!";
        else

            for (clsBankUser& User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "___________________________________________________________\n" << endl;

    }
};

