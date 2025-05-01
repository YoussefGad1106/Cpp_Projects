#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsTransactionMenu.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
#include "clsGlobal.h"

using namespace std;

class clsTransfer : protected clsScreen
{
private:

	static void _Print(clsBankClient& Client)
	{

		cout << "\n\t\t\t\t\tClient Card :";
		cout << "\n\t\t\t\t\t__________________________________";
		cout << "\n\t\t\t\t\tFull Name       : " << Client.GetFullName();
		cout << "\n\t\t\t\t\tAccount Number  : " << Client.GetAccountNumber();
		cout << "\n\t\t\t\t\tAccount Balance : " << Client.AccountBalance;
		cout << "\n\t\t\t\t\t__________________________________\n\n";
	}

	static clsBankClient _GetBankClientObject(string Message)
	{
		string AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\t" + Message);

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tClient NOT exist. Enter another Account Number : ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return Client;
	}

public :

	static void ShowTransferMenu()
	{
		_DrawScreenHeader("Transfer Screen");

		clsBankClient SenderClient = _GetBankClientObject("Enter the Sender Account Number : ");
		_Print(SenderClient);

		clsBankClient AccepterClient = _GetBankClientObject("Enter the Accepter Account Number : ");
		_Print(AccepterClient);

		double TransferAmount = clsInputValidate::ReadNumber<double>("\t\t\t\t\tEnter the Transfer Amount : ", "\t\t\t\t\tInvalid Input Please Try Again : ");

		while (TransferAmount > SenderClient.AccountBalance)
		{
			TransferAmount = clsInputValidate::ReadNumber<double>("\t\t\t\t\tInsufficient Balance. Please re-enter valid amount : ", "\t\t\t\t\tInvalid Input Please Try Again : ");
		}

		char choice;
		cout << "\n\t\t\t\t\tAre you sure you want to confirm this Transfer ? y/n : ";
		cin >> choice;

		if (tolower(choice) == 'y')
		{
			SenderClient.Transfer(AccepterClient, TransferAmount);
			cout << "\n\n\t\t\t\t\tTransfer has been done Successfully !!!";
			_Print(SenderClient);
			_Print(AccepterClient);
			return;
		}

		cout << "\n\n\t\t\t\t\tTransfer Process has been Cancelled!!!";
	}

};

