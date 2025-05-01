#pragma once
#include <iostream>
#include "clsMainMenu.h"
#include "clsScreen.h"
#include "clsGlobal.h"
#include "clsBankUser.h"
#include "clsInputValidation.h"

using namespace std;

class clsLogin : protected clsScreen
{
private :

	static bool _Login()
	{
		string UserName = "", UserPassword = "";
		short NumberOfAttempts = 3;

		system("cls");
		_DrawScreenHeader("Log In Screen");

		do
		{
			UserName = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's Name : ");
			UserPassword = clsInputValidate::ReadValidString("\t\t\t\t\tEnter the User's Password : ");

			LoggedInUser = clsBankUser::Find(UserName, UserPassword);

			if (!clsBankUser::IsUserExist(LoggedInUser.GetUserName()))
			{
				NumberOfAttempts--;
				cout << "\n\n\t\t\t\t\tInvalid UserName / Password\n";
				cout << "\t\t\t\t\tYou still have " << NumberOfAttempts << " trial(s) before system lock.\n";
			}

		} while (LoggedInUser.IsEmpty() && NumberOfAttempts != 0);

		if (NumberOfAttempts == 0)
		{
			system("cls");
			cout << "\n\t\t\t\t\tSystem has been Locked !!!\n";
			return false;
		}

		return true;
	}


public :

	static void ShowLogInScreen()
	{
		while (_Login())
		{
			LoggedInUser.LoginRegisterOnFile();
			clsMainMenu::ShowMainMenu();
		}
	}
};

