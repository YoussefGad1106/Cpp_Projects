#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidation.h"

using namespace std;

class clsWithdraw : protected clsScreen
{
private:

    static void _Print(clsBankClient& Client)
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

    static void BalanceWithdraw()
    {
        _DrawScreenHeader("Withdraw Screen");
        string AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Account Number : ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tClient NOT Exist. Please Enter Another Account Number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);

        double WithdrawAmount = clsInputValidate::ReadNumber<double>("\t\t\t\t\tEnter the Withdraw Amount : ", "\t\t\t\t\tInvalid Input Please Try Again : ");

        char choice;
        cout << "\n\t\t\t\t\tAre you sure you want to confirm this Withdraw ? y/n : ";
        cin >> choice;

        if (tolower(choice) == 'y')
        {
            if (Client.Withdraw(WithdrawAmount))
            {
                cout << "\n\t\t\t\t\tWithdraw Amount : " << WithdrawAmount;
                cout << "\n\t\t\t\t\tClient's New Balance : " << Client.AccountBalance;
                return;
            }
            else
            {
                cout << "\n\t\t\t\t\tError : Insufficient Balance for Withdraw.";
                cout << "\n\t\t\t\t\tWithdraw Amount : " << WithdrawAmount;
                cout << "\n\t\t\t\t\tClient's Current Balance : " << Client.AccountBalance;
                return;
            }
        }

        cout << "\n\t\t\t\t\tThe Withdraw Operation has been Cancelled\n";


    }
};

