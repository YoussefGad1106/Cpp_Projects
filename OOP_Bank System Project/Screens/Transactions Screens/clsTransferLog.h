#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsDate.h"
#include "clsGlobal.h"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLog : protected clsScreen
{
private:

    static void _PrintTransferLogLine(clsBankClient::stTransferLogData Transfer)
    {
        cout << "| " << left << setw(20) << Transfer.DateTime;
        cout << "| " << left << setw(13) << Transfer.SenderClientAccountNumber;
        cout << "| " << left << setw(15) << Transfer.AccepterClientAccountNumber;
        cout << "| " << left << setw(10)  << Transfer.TransferAmount;
        cout << "| " << left << setw(15) << Transfer.SenderClientAccountBalance;
        cout << "| " << left << setw(17) << Transfer.AccepterClientAccountBalance;
        cout << "| " << left << setw(10) << Transfer.UserName;
    }

    static clsBankClient::stTransferLogData _ConvertTransferLogLineToStructData(string Line, string Separator = "#//#")
    {
        vector<string> vTransferData;
        vTransferData = clsString::Split(Line, Separator);
        clsBankClient::stTransferLogData TransferLogData;
        
        TransferLogData.DateTime = vTransferData[0];
        TransferLogData.SenderClientAccountNumber = vTransferData[1];
        TransferLogData.AccepterClientAccountNumber = vTransferData[2];
        TransferLogData.TransferAmount = stod(vTransferData[3]);
        TransferLogData.SenderClientAccountBalance = stof(vTransferData[4]);
        TransferLogData.AccepterClientAccountBalance = stof(vTransferData[5]);
        TransferLogData.UserName = vTransferData[6];

        return TransferLogData;
    }

    static vector <clsBankClient::stTransferLogData> _LoadTransferLogsDataFromFile()
    {
        fstream MyFile;
        string Line;
        vector <clsBankClient::stTransferLogData> vTransfers;

        MyFile.open("Transfer Log.txt", ios::in);

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                vTransfers.push_back(_ConvertTransferLogLineToStructData(Line));
            }
        }

        MyFile.close();
        return vTransfers;
    }

public:

    static void ShowTransferLogMenu()
    {
        vector <clsBankClient::stTransferLogData> vTransfers = _LoadTransferLogsDataFromFile();

        _DrawScreenHeader("Transfer Log Menu", to_string(vTransfers.size()) + " Record(s).");
        cout << "\n_______________________________________________";
        cout << "____________________________________________________________________\n" << endl;

        cout << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(13) << "Sender AccNo";
        cout << "| " << left << setw(15) << "Accepter AccNo";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(15) << "Sender Balance";
        cout << "| " << left << setw(17) << "Accepter Balance";
        cout << "| " << left << setw(10) << "UserName";
        cout << "\n_______________________________________________";
        cout << "____________________________________________________________________\n" << endl;

        if (vTransfers.empty())
            cout << "\t\t\t  No Previous Transfers History!!";
        else

            for (clsBankClient::stTransferLogData Transfer : vTransfers)
            {

                _PrintTransferLogLine(Transfer);
                cout << endl;
            }

        cout << "\n_______________________________________________";
        cout << "____________________________________________________________________\n" << endl;
    }

};

