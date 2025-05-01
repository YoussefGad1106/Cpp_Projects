#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsFindClient : protected clsScreen
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

public:

	static void FindClient()
	{
		if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enFindClient))
		{
			return;
		}
		_DrawScreenHeader("Find A Client");

		string AccountNumber = clsInputValidate::ReadValidString("\n\t\t\t\t\tPlease Enter Account Number: ");

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (Client1.IsEmpty())
		{
			cout << "\n\t\t\t\t\tClient with this Account Number is NOT found\n";
			return;
		}

		cout << "\n\n\t\t\t\t\tClient has been Found\n";
		_Print(Client1);

	}
};