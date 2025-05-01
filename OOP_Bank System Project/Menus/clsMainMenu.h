#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsListClients.h"
#include "clsAddClient.h"
#include "clsDeleteClient.h"
#include "clsUpdateClient.h"
#include "clsFindClient.h"
#include "clsTransactionMenu.h"
#include "clsManageUsersMenu.h"
#include "clsLogin.h"
#include "clsLoginRegister.h"
#include "clsCurrencyExchangeMenu.h"

using namespace std;

class clsMainMenu : protected clsScreen
{
private :

	enum enMainMenuOptions
	{
		enClientList = 1, enAddClient = 2, enDeleteClient = 3,
		enUpdateClient = 4, enFindClient = 5, enTransactionMenu = 6,
		enManageUsers = 7, enLoginRegister = 8, enCurrencyExchangeMenu = 9, enLogOut = 10
	};

	static short _ReadMainMenuOption()
	{
		short Option = clsInputValidate::ReadNumberBetween("\n\t\t\t\t\tEnter Your Choice [1-10] : ", "\t\t\t\t\tError : Please Enter a Number from 1 to 10", 1, 10);
		return Option;
	}

	static void _ShowClientList()
	{
		system("cls");
		clsListClients::ShowClientsList();
	}

	static void _AddNewClient()
	{
		system("cls");
		clsAddClient::AddNewClient();
	}

	static void _DeleteClient()
	{
		system("cls");
		clsDeleteClient::DeleteClient();
	}

	static void _UpdateClient()
	{
		system("cls");
		clsUpdateClient::UpdateClient();
	}

	static void _FindClient()
	{
		system("cls");
		clsFindClient::FindClient();
	}

	static void _TransactionMenu()
	{
		system("cls");
		clsTransactionMenu::ShowTransactionMenu();
	}

	static void _ManageUsersMenu()
	{
		clsManageUsersMenu::ShowManageUsersMenu();
	}

	static void _ShowLoginRegisterMenu()
	{
		system("cls");
		clsLoginRegister::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMenu()
	{
		system("cls");
		clsCurrencyExchangeMenu::ShowCurrencyExchangeMenu();
	}

	static void _LogOut()
	{
		LoggedInUser = clsBankUser::Find("");
	}

	static void _GetBackToMainMenu()
	{
		cout << "\n\n\n Press Any Key To Go Back To Main Menu...." << endl;

		system("pause > 0");
		ShowMainMenu();
	}

	static void _PerformMainMenuOption(enMainMenuOptions option)
	{

		switch (option)
		{
		case clsMainMenu::enClientList:
			_ShowClientList();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enAddClient:
			_AddNewClient();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enDeleteClient:
			_DeleteClient();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enUpdateClient:
			_UpdateClient();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enFindClient:
			_FindClient();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enTransactionMenu:
			_TransactionMenu();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enManageUsers:
			_ManageUsersMenu();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enLoginRegister:
			_ShowLoginRegisterMenu();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enCurrencyExchangeMenu :
			_ShowCurrencyExchangeMenu();
			_GetBackToMainMenu();
			break;

		case clsMainMenu::enLogOut:
			_LogOut();
			break;

		}
	}

public :

	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("Main Menu");


		cout << setw(40) << left << "\t\t\t\t\t[1]-  Show Clients List" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[2]-  Add New Client" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[3]-  Delete a Client" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[4]-  Update a Client" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[5]-  Find a Client" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[6]-  Transactions Menu" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[7]-  Manage Users Menu" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[8]-  Login Register Menu" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[9]-  Currency Exchange Menu" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[10]- Log Out" << endl;

				 
		_PerformMainMenuOption((enMainMenuOptions) _ReadMainMenuOption());
	}
};


