#pragma once
#include <iostream>
#include "clsBankUser.h"
#include "clsScreen.h"
using namespace std;

class clsUpdateUser : protected clsScreen
{
private:

	static void _ReadUserInfo(clsBankUser& User)
	{
		User.FirstName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's First Name : ");
		User.LastName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's Last Name : ");
		User.Email = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's Email : ");
		User.Phone = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's Phone : ");
		User.UserPassword = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's Password : ");
		User.Permissions = _ReadAccessPermissions();
	}

	static bool _ReadYOrN(string InvalidMessage = "\n\t\t\t\t\tInvalid Answer [Y - N] : ")
	{
		char Answer = ' ';
		cin >> Answer;

		while (toupper(Answer) != 'Y' && toupper(Answer) != 'N')
		{
			cout << InvalidMessage;
			cin >> Answer;
		}

		return toupper(Answer) == 'Y';
	}

	static short _ReadAccessPermissions()
	{
		short Permissions = 0;

		cout << "\n\t\t\t\t\tDo you want to give this user full access ? y/n : ";
		if (_ReadYOrN())
			return -1;

		cout << "\n\t\t\t\t\tWhat do you Want to give access to ? ";

		cout << "\n\t\t\t\t\tShow Clients List ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enListClient;

		cout << "\n\t\t\t\t\tAdd Client ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enAddClient;

		cout << "\n\t\t\t\t\tDelete Client ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enDeleteClient;

		cout << "\n\t\t\t\t\tUpdate Client ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enUpdateClient;

		cout << "\n\t\t\t\t\tFind Client ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enFindClient;

		cout << "\n\t\t\t\t\tTransaction Menu ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enTransactionMenu;

		cout << "\n\t\t\t\t\tManage Users Menu ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enManageUsersMenu;

		cout << "\n\t\t\t\t\tLogin Register Menu ? ";
		if (_ReadYOrN())
			Permissions += clsBankUser::enMainMenuPermissions::enLoginRegister;


		return Permissions;

	}

	static void _Print(clsBankUser& User)
	{

		cout << "\n\t\t\t\t\tUser Card :";
		cout << "\n\t\t\t\t\t__________________________________";
		cout << "\n\t\t\t\t\tFirst Name      : " << User.FirstName;
		cout << "\n\t\t\t\t\tLast Name       : " << User.LastName;
		cout << "\n\t\t\t\t\tFull Name       : " << User.GetFullName();
		cout << "\n\t\t\t\t\tEmail           : " << User.Email;
		cout << "\n\t\t\t\t\tPhone           : " << User.Phone;
		cout << "\n\t\t\t\t\tAccount Number  : " << User.GetUserName();
		cout << "\n\t\t\t\t\tUser Password   : " << User.UserPassword;
		cout << "\n\t\t\t\t\tPermissions     : " << User.Permissions;
		cout << "\n\t\t\t\t\t__________________________________\n";
	}

public:

	static void UpdateUser()
	{
		_DrawScreenHeader("Update A User");
		string UserName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's User Name : ");

		while (!clsBankUser::IsUserExist(UserName))
		{
			UserName = clsInputValidate::ReadValidString("\n\t\t\t\t\tThis User Name is NOT found. Please Enter Another One : ");
		}

		clsBankUser User = clsBankUser::Find(UserName);

		if (User.GetUserName() == "Admin")
		{
			cout << "\n\t\t\t\t\tAdmin User cannot be Updated !!!";
			return;
		}

		_Print(User);

		cout << "\n\t\t\t\t\tUpdating User Info : \n";
		cout << "\t\t\t\t\t____________________________\n";

		_ReadUserInfo(User);

		clsBankUser::enSaveResults SaveResult = User.Save();


		switch (SaveResult)
		{
			// case of trying to save an empty object came from the find function
		case clsBankUser::enSaveResults::svFailedEmptyObject:
			cout << "\n\t\t\t\t\tError : User was not saved because it is an Empty User.";
			break;

		case clsBankUser::enSaveResults::svSuccesseded:
			cout << "\n\t\t\t\t\tUser has been Updated Successfully :)";
			break;

		case clsBankUser::enSaveResults::svFailedUserNameExist:
			cout << "\n\t\t\t\t\tError : User with same User Name already Exists.";
			break;
		}
	}
};

