#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsListCurrencies.h"
#include "clsFindCurrency.h"
#include "clsUpdateRate.h"
#include "clsCurrencyCalculator.h"
using namespace std;

class clsCurrencyExchangeMenu : protected clsScreen
{
private :

	enum enCurrencyExchangeMenuOptions
	{
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5
	};

	static short _ReadCurrencyExchangeMenuOption()
	{
		short Option = clsInputValidate::ReadNumberBetween("\n\t\t\t\t\tEnter Your Choice [1 - 5] : ", "\t\t\t\t\tError : Please Enter a Number from 1 to 5", 1, 5);
		return Option;
	}

	static void _ListCurrencies()
	{
		system("cls");
		clsListCurrencies::ShowListCurrenciesScreen();
	}

	static void _FindCurrency()
	{
		system("cls");
		clsFindCurrency::FindCurrency();
	}

	static void _UpdateRate()
	{
		system("cls");
		clsUpdateRate::UpdateCurrencyRate();
	}

	static void _CurrencyCalculator()
	{
		system("cls");
		clsCurrencyCalculator::ShowCurrencyCalculator();
	}

	static void _GetBackToCurrencyExchangeMenu()
	{
		cout << "\n\n\n Press Any Key To Go Back To Currency Exchange Menu...." << endl;

		system("pause > 0");
		ShowCurrencyExchangeMenu();
	}

	static void _PerformCurrencyExchangeMenuOption(enCurrencyExchangeMenuOptions Option)
	{
		switch (Option)
		{
		case clsCurrencyExchangeMenu::eListCurrencies:
			_ListCurrencies();
			_GetBackToCurrencyExchangeMenu();
			break;

		case clsCurrencyExchangeMenu::eFindCurrency:
			_FindCurrency();
			_GetBackToCurrencyExchangeMenu();
			break;

		case clsCurrencyExchangeMenu::eUpdateRate:
			_UpdateRate();
			_GetBackToCurrencyExchangeMenu();
			break;

		case clsCurrencyExchangeMenu::eCurrencyCalculator:
			_CurrencyCalculator();
			_GetBackToCurrencyExchangeMenu();
			break;

		case clsCurrencyExchangeMenu::eMainMenu:
			break;
		}
	}

public :

	static void ShowCurrencyExchangeMenu()
	{
		system("cls");
		_DrawScreenHeader("Currency Exchange Menu");

		cout << setw(40) << left << "\t\t\t\t\t[1]- List Currencies" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[2]- Find Currency" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[3]- Update Rate" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[4]- Currency Calculator" << endl;
		cout << setw(40) << left << "\t\t\t\t\t[5]- Main Menu" << endl;

		_PerformCurrencyExchangeMenuOption((enCurrencyExchangeMenuOptions)_ReadCurrencyExchangeMenuOption());
	}
};

