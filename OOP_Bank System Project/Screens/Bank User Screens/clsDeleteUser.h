#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsBankUser.h"
#include "clsInputValidation.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteUser : protected clsScreen
{
private:

    static void _Print(clsBankUser& User)
    {

        cout << "\n\t\t\t\t\tUser Card :";
        cout << "\n\t\t\t\t\t__________________________________";
        cout << "\n\t\t\t\t\tFirst Name      : " << User.FirstName;
        cout << "\n\t\t\t\t\tLast Name       : " << User.LastName;
        cout << "\n\t\t\t\t\tFull Name       : " << User.GetFullName();
        cout << "\n\t\t\t\t\tEmail           : " << User.Email;
        cout << "\n\t\t\t\t\tPhone           : " << User.Phone;
        cout << "\n\t\t\t\t\tUser Name       : " << User.GetUserName();
        cout << "\n\t\t\t\t\tUser Password   : " << User.UserPassword;
        cout << "\n\t\t\t\t\tPermissions     : " << User.Permissions;
        cout << "\n\t\t\t\t\t__________________________________\n";
    }

public:

    static void DeleteUser()
    {
        _DrawScreenHeader("Delete An User");

        string UserName = clsInputValidate::ReadValidString("\n\t\t\t\t\tPlease Enter User Name : ");

        while (!clsBankUser::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadValidString("\n\t\t\t\t\tUser Name is not found, choose another one: ");
        }

        clsBankUser User1 = clsBankUser::Find(UserName);

        if (User1.GetUserName() == "Admin")
        {
            cout << "\n\t\t\t\t\tAdmin User cannot be Deleted !!!";
            return;
        }
        
        _Print(User1);

        cout << "\n\t\t\t\t\tAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (User1.Delete())
            {
                cout << "\n\t\t\t\t\tUser Deleted Successfully :-)\n";
            }
            else
            {
                cout << "\n\t\t\t\t\tError User Was not Deleted\n";
            }
        }
    }
};

