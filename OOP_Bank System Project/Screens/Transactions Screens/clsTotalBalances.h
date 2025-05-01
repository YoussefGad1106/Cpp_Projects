#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsScreen.h"

using namespace std;

class clsTotalBalances : protected clsScreen
{

private :

    static void PrintClientRecordBalance(clsBankClient Client)
    {
        cout << "| " << setw(20) << left << Client.GetAccountNumber();
        cout << "| " << setw(30) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.GetAccountBalance();
    }

public:

    static void ShowTotalBalances()
    {

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        double TotalBalances = clsBankClient::GetTotalBalances();

        _DrawScreenHeader("Total Balances Screen", "  " + to_string(vClients.size()) + " Client(s).");

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(20) << "Account Number";
        cout << "| " << left << setw(30) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.empty())
            cout << "\t\t\t  No Clients Available In the System!";
        else

            for (clsBankClient& Client : vClients)
            {

                PrintClientRecordBalance(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "\t\t\t\t Clients Total Balances : " << TotalBalances << endl;
        cout << "\t\t\t\t (" << clsUtil::NumberToText(TotalBalances) << ") " << endl;

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

