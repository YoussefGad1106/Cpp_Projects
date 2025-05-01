#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClient : protected clsScreen
{
private:

    static void _Print(clsBankClient &Client)
    {

        cout << "\n\t\t\t\t\tClient Card :";
        cout << "\n\t\t\t\t\t__________________________________";
        cout << "\n\t\t\t\t\tFirst Name      : " << Client.FirstName;
        cout << "\n\t\t\t\t\tLast Name       : " << Client.LastName;
        cout << "\n\t\t\t\t\tFull Name       : " << Client.GetFullName();
        cout << "\n\t\t\t\t\tEmail           : " << Client.Email;
        cout << "\n\t\t\t\t\tPhone           : " << Client.Phone;
        cout << "\n\t\t\t\t\tAccount Number  : " << Client.GetAccountNumber();
        cout << "\n\t\t\t\t\tPassword        : " << Client.PinCode;
        cout << "\n\t\t\t\t\tAccount Balance : " << Client.AccountBalance;
        cout << "\n\t\t\t\t\t__________________________________\n";
    }

public:

    static void DeleteClient()
    {
        if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enDeleteClient))
        {
            return;
        }
        _DrawScreenHeader("Delete A Client");

        string AccountNumber = clsInputValidate::ReadValidString("\n\t\t\t\t\tPlease Enter Account Number: ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadValidString("\n\t\t\t\t\tAccount number is not found, choose another one: ");
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);

        cout << "\n\t\t\t\t\tAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (Client1.Delete())
            {
                cout << "\n\t\t\t\t\tClient Deleted Successfully :-)\n";
            }
            else
            {
                cout << "\n\t\t\t\t\tError Client Was not Deleted\n";
            }
        }
    }
};

