#include <iostream>
#include "clsBankUser.h"
#include "clsScreen.h"

using namespace std;

class clsFindUser : protected clsScreen
{
private:

	static void _Print(clsBankUser& User)
	{

		cout << "\n\t\t\t\t\tUser Card :";
		cout << "\n\t\t\t\t\t__________________________________";
		cout << "\n\t\t\t\t\tFirst Name      : " << User.FirstName;
		cout << "\n\t\t\t\t\tLast Name       : " << User.LastName;
		cout << "\n\t\t\t\t\tFull Name       : " << User.GetFullName();
		cout << "\n\t\t\t\t\tEmail           : " << User.Email;
		cout << "\n\t\t\t\t\tPhone           : " << User.Phone;
		cout << "\n\t\t\t\t\tUser Name       : " << User.GetUserName();
		cout << "\n\t\t\t\t\tUser Password   : " << User.UserPassword;
		cout << "\n\t\t\t\t\tPermissions     : " << User.Permissions;
		cout << "\n\t\t\t\t\t__________________________________\n";
	}

public:

	static void FindUser()
	{
		_DrawScreenHeader("Find An User");

		string UserName = clsInputValidate::ReadValidString("\n\t\t\t\t\tPlease Enter User Name: ");

		clsBankUser User1 = clsBankUser::Find(UserName);

		if (User1.IsEmpty())
		{
			cout << "\n\t\t\t\t\tUser with this User Name is NOT found\n";
			return;
		}

		cout << "\n\n\t\t\t\t\tUser has been Found\n";
		_Print(User1);

	}
};