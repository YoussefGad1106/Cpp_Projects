#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsBankUser.h"
#include "clsInputValidation.h"
#include "clsScreen.h"


using namespace std;

class clsAddUser : protected clsScreen
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


public:

	static void AddNewUser()
	{
		clsScreen::_DrawScreenHeader("Adding New User");

		string UserName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the New User's User Name : ");

		while (clsBankUser::IsUserExist(UserName))
		{
			clsInputValidate::ReadValidString("\t\t\t\t\tUser Already Exists Please Enter another User Name : ");
		}

		clsBankUser AddedUser = clsBankUser::NewUserObject(UserName);

		cout << "\n\t\t\t\t\tAdding New User : \n";
		cout << "\t\t\t\t\t____________________________\n";

		_ReadUserInfo(AddedUser);

		clsBankUser::enSaveResults SaveResult = AddedUser.Save();

		switch (SaveResult)
		{
		case clsBankUser::enSaveResults::svFailedEmptyObject:

			cout << "\n\t\t\t\t\tError : Account was not saved because it is an Empty User.";
			break;

		case clsBankUser::enSaveResults::svSuccesseded:
			cout << "\n\t\t\t\t\tUser has been Added Successfully :)";
			break;

		case clsBankUser::enSaveResults::svFailedUserNameExist:
			cout << "\n\t\t\t\t\tError : User with same User Name already Exists.";
			break;
		}
	}
};

