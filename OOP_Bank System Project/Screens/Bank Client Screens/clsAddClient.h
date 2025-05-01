#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsScreen.h"


using namespace std;

class clsAddClient : protected clsScreen
{
private :

	static void ReadClientInfo(clsBankClient& Client)
	{
		Client.FirstName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's First Name : ");
		Client.LastName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Last Name : ");
		Client.Email = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Email : ");
		Client.Phone = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Phone : ");
		Client.PinCode = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's PinCode : ");
		Client.AccountBalance = clsInputValidate::ReadNumber<float>("\t\t\t\t\tEnter the Client's Account Balance : ", "\t\t\t\t\tInvalid Input Please Enter a valid float Number");
	}

public :

	static void AddNewClient()
	{

		if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enAddClient))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("Adding New Client");

		string AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the New Client's Account Number : ");

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tClient Already Exists Please Enter another Account Number : ");
		}

		clsBankClient AddedClient = clsBankClient::NewClientObject(AccountNumber);

		cout << "\n\t\t\t\t\tAdding New Client : \n";
		cout << "\t\t\t\t\t____________________________\n";

		ReadClientInfo(AddedClient);

		clsBankClient::enSaveResults SaveResult = AddedClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svFailedEmptyObject:

			cout << "\n\t\t\t\t\tError : Account was not saved because it is an Empty Client.";
			break;

		case clsBankClient::enSaveResults::svSuccesseded:
			cout << "\n\t\t\t\t\tClient has been Added Successfully :)";
			break;

		case clsBankClient::enSaveResults::svFailedAccountNumberExist :
			cout << "\n\t\t\t\t\tError : Client with same Account Number already Exists.";
			break;
		}
	}
};

