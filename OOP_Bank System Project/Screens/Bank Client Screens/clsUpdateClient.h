#pragma once
#include <iostream>
#include "clsBankClient.h"
using namespace std;

class clsUpdateClient : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.FirstName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's First Name : ");
		Client.LastName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Last Name : ");
		Client.Email = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Email : ");
		Client.Phone = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Phone : ");
		Client.PinCode = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's PinCode : ");
		Client.AccountBalance = clsInputValidate::ReadNumber<float>("\t\t\t\t\tEnter the Client's Account Balance : ", "\t\t\t\t\tInvalid Input Please Enter a valid float Number");
	}


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
	
	static void UpdateClient()
	{
		if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enUpdateClient))
		{
			return;
		}
		_DrawScreenHeader("Update A Client");
		string AccountNumber = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the Client's Account Number : ");

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadValidString("\n\t\t\t\t\tThis Account Number is NOT found. Please Enter Another One : ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		cout << "\n\t\t\t\t\tUpdating Client Info : \n";
		cout << "\t\t\t\t\t____________________________\n";

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult = Client.Save();


		switch (SaveResult)
		{
			// case of trying to save an empty object came from the find function
		case clsBankClient::enSaveResults::svFailedEmptyObject:
			cout << "\n\t\t\t\t\tError : Account was not saved because it is an Empty Client.";
			break;

		case clsBankClient::enSaveResults::svSuccesseded:
			cout << "\n\t\t\t\t\tClient has been Updated Successfully :)";
			break;
		
		case clsBankClient::enSaveResults::svFailedAccountNumberExist:
			cout << "\n\t\t\t\t\tError : Client with same Account Number already Exists.";
			break;
		}
	}
};

