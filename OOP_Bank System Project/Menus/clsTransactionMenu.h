#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsTotalBalances.h"
#include "clsDeposit.h"
#include "clsWithdraw.h"
#include "clsTransfer.h"
#include "clsTransferLog.h"

using namespace std;

class clsTransactionMenu : protected clsScreen
{
private:

	enum enTransactionMenuOptions
	{
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransferWindow = 4,
		eTransferLogMenu = 5, eMainMenu = 6
	};

	static short _ReadTransactionMenuOption()
	{
		short Option = clsInputValidate::ReadNumberBetween("\n\t\t\t\t\tEnter Your Choice [1 - 6] : ", "\t\t\t\t\tError : Please Enter a Number from 1 to 6", 1, 6);
		return Option;
	}

	static void _Deposit()
	{
		system("cls");
		clsDeposit::BalanceDeposit();
	}

	static void _Withdraw()
	{
		system("cls");
		clsWithdraw::BalanceWithdraw();
	}

	static void _TotalBalances()
	{
		system("cls");
		clsTotalBalances::ShowTotalBalances();
	}

	static void _TransferWindow()
	{
		system("cls");
		clsTransfer::ShowTransferMenu();
	}

	static void _TransferLogMenu()
	{
		system("cls");
		clsTransferLog::ShowTransferLogMenu();
	}

	static void _GetBackToTransactionMenu()
	{
		cout << "\n\n\n Press Any Key To Go Back To Transaction Menu...." << endl;

		system("pause > 0");
		ShowTransactionMenu();
	}

	static void _PerformTransactionMenuOption(enTransactionMenuOptions Option)
	{
		switch (Option)
		{
		case clsTransactionMenu::eDeposit:
			_Deposit();
			_GetBackToTransactionMenu();
			break;

		case clsTransactionMenu::eWithdraw:
			_Withdraw();
			_GetBackToTransactionMenu();
			break;

		case clsTransactionMenu::eTotalBalances:
			_TotalBalances();
			_GetBackToTransactionMenu();
			break;

		case clsTransactionMenu::eTransferWindow:
			_TransferWindow();
			_GetBackToTransactionMenu();
			break;

		case clsTransactionMenu::eTransferLogMenu :
			_TransferLogMenu();
			_GetBackToTransactionMenu();
			break;

		case clsTransactionMenu::eMainMenu:
			break;
		}
	}

public :

	static void ShowTransactionMenu()
	{
		if (!_CheckMenuAccessState(clsBankUser::enMainMenuPermissions::enTransactionMenu))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("Transaction Menu");

		cout << setw(40) << left << "\t\t\t\t\t[1]- Deposit" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[2]- Withdraw" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[3]- Total Balances" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[4]- Transfer Window" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[5]- Transfer Log Menu" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[6]- Main Menu" << endl;

		_PerformTransactionMenuOption((enTransactionMenuOptions)_ReadTransactionMenuOption());

	}
};

