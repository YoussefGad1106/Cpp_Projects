#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidation.h"

using namespace std;

class clsDeposit : protected clsScreen
{
private :
	
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

public :

    static void BalanceDeposit()
    {
        _DrawScreenHeader("Deposit Screen");
        string AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Account Number : ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tClient NOT Exist. Please Enter Another Account Number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);

        double DepositAmount = clsInputValidate::ReadNumber<double>("\t\t\t\t\tEnter the Deposit Amount : ", "\t\t\t\t\tInvalid Input Please Try Again : ");
        
        char choice;
        cout << "\n\t\t\t\t\tAre you sure you want to confirm this Deposit ? y/n : ";
        cin >> choice;

        if (tolower(choice) == 'y')
        {
            Client.Deposit(DepositAmount);
            cout << "\n\t\t\t\t\tDeposit Amount : " << DepositAmount;
            cout << "\n\t\t\t\t\tClient's New Balance is : " << Client.AccountBalance << endl;
            return;
        }

        cout << "\n\t\t\t\t\tThe Deposit Operation has been Cancelled\n";
        

    }
};

