#pragma once
#include <iostream>
#include <iomanip>
#include "clsGlobal.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected :

	static void _DrawScreenHeader(string title, string subTitle = "")
	{
       cout << "\t\t\t\t\t_______________________________________________";
	   cout << "\n\n\t\t\t\t\t\t\t" << title;

		if (subTitle != "")
		{
			cout << "\n\t\t\t\t\t\t\t" << subTitle;
		}
		cout << "\n\t\t\t\t\t_______________________________________________\n";

		_DisplayLoggedInUser();
		_DisplayTodaysDate();

		cout << "\n\n";
        
	}

	static bool _CheckMenuAccessState(clsBankUser::enMainMenuPermissions Permission)
	{
		if (!LoggedInUser.CheckAccessPermission(Permission))
		{
			_DrawScreenHeader("   Access Denied !!", "Please Contact your Admin");
			return false;
		}
		else
		{
			return true;
		}

	}

	static void _DisplayLoggedInUser()
	{
		cout << "\n\t\t\t\t\t User : " << LoggedInUser.GetUserName() << endl;
	}

	static void _DisplayTodaysDate()
	{
		cout << "\t\t\t\t\t ";
		clsDate::PrintDate(clsDate());
	}
};


