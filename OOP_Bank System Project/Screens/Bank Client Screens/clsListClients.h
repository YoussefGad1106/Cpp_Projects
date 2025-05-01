#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsListClients : protected clsScreen
{

private :

    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(25) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }
public :

    static void ShowClientsList()
    {
        if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enListClient))
        {
            return;
        }

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        _DrawScreenHeader("Clients List", to_string(vClients.size()) + " Client(s).");
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.empty())
            cout << "\t\t\t  No Clients Available In the System!";
        else

            for (clsBankClient &Client : vClients)
            {

                _PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

