#pragma once
#include <iostream>
#include "clsInputValidation.h"
#include "clsScreen.h"
#include "clsListUsers.h"
#include "clsDeleteUser.h"
#include "clsFindUser.h"
#include "clsAddUser.h"
#include "clsUpdateUser.h"

using namespace std;


class clsManageUsersMenu : protected clsScreen
{
private :

	enum enManageUsersMenuOptions 
	{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
	};

	static short _ReadManageUsersMenuOption()
	{
		short Option = clsInputValidate::ReadNumberBetween("\n\t\t\t\t\tEnter Your Choice [1-6] : ", "\t\t\t\t\tError : Please Enter a Number from 1 to 6", 1, 6);
		return Option;
	}

	static void _ListUsers()
	{
		system("cls");
		clsListUsers::ShowUsersList();
	}

	static void _AddNewUser()
	{
		system("cls");
		clsAddUser::AddNewUser();
	}

	static void _DeleteUser()
	{
		system("cls");
		clsDeleteUser::DeleteUser();
	}

	static void _UpdateUser()
	{
		system("cls");
		clsUpdateUser::UpdateUser();
	}

	static void _FindUser()
	{
		system("cls");
		clsFindUser::FindUser();
	}

	static void _GetBackToManageUsersMenu()
	{
		cout << "\n\n\n Press Any Key To Go Back To Manage Users Menu...." << endl;

		system("pause > 0");
		ShowManageUsersMenu();
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOptions option)
	{
		switch (option)
		{
		case clsManageUsersMenu::eListUsers:
			_ListUsers();
			_GetBackToManageUsersMenu();
			break;

		case clsManageUsersMenu::eAddNewUser:
			_AddNewUser();
			_GetBackToManageUsersMenu();
			break;

		case clsManageUsersMenu::eDeleteUser:
			_DeleteUser();
			_GetBackToManageUsersMenu();
			break;

		case clsManageUsersMenu::eUpdateUser:
			_UpdateUser();
			_GetBackToManageUsersMenu();
			break;
			
		case clsManageUsersMenu::eFindUser:
			_FindUser();
			_GetBackToManageUsersMenu();
			break;

		case clsManageUsersMenu::eMainMenu:
			break;
		}
	}

public :

	static void ShowManageUsersMenu()
	{
		if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enManageUsersMenu))
		{
			return;
		}
		system("cls");

		_DrawScreenHeader("Manage Users Menu");

		cout << setw(40) << left << "\t\t\t\t\t[1]- List Users" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[2]- Add New User" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[3]- Delete User" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[4]- Update User" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[5]- Find User" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[6]- Main Menu" << endl;

		_PerformManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());

	}

};

