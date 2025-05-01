#pragma once
#include <iostream>
#include <vector>
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"
using namespace std;

class clsCurrencyCalculator : protected clsScreen
{
private :

	static void _Print(clsCurrency Currency)
	{

		cout << "\n\n\t\t\t\t\tCurrency Card :";
		cout << "\n\t\t\t\t\t__________________________________";
		cout << "\n\t\t\t\t\tCountry Name        : " << Currency.GetCountryName();
		cout << "\n\t\t\t\t\tCurrency Code       : " << Currency.GetCurrencyCode();
		cout << "\n\t\t\t\t\tCurrency Name       : " << Currency.GetCurrencyName();
		cout << "\n\t\t\t\t\tRate/(1$) =         : " << Currency.GetRate();
		cout << "\n\t\t\t\t\t__________________________________\n";
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

	static clsCurrency _GetCurrencyByCurrencyCode(string Message)
	{
		string CurrencyCode = clsInputValidate::ReadValidString("\t\t\t\t\t" + Message);

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			CurrencyCode = clsInputValidate::ReadValidString("\t\t\t\t\tCurrency NOT found. Please try again : ");
		}

		clsCurrency Currency = clsCurrency::Find(CurrencyCode);

		return Currency;
	}

	static float _ReadExchangeAmount()
	{
		float amount = clsInputValidate::ReadNumber<float>("\t\t\t\t\tEnter the Amount of the exchange : ", "\t\t\t\t\tInvalid input. please try again : ");
		return amount;
	}

	static void _PrintExchangeResult(clsCurrency CurrencyFrom, clsCurrency CurrencyTo, float amount)
	{
		if (clsString::UpperAllString(CurrencyFrom.GetCurrencyCode()) != "USD")
		{
			cout << "\n\n\t\t\t\t\tConverting From Currency : ";
			cout << "\n\t\t\t\t\t_____________________________";
			_Print(CurrencyFrom);
		}

		if (clsString::UpperAllString(CurrencyTo.GetCurrencyCode()) != "USD")
		{
			cout << "\n\n\t\t\t\t\tConverting To Currency : ";
			cout << "\n\t\t\t\t\t_____________________________";
			_Print(CurrencyTo);
		}

		float ExchangeResult = CurrencyFrom.ExchangeTwoCurrencies(CurrencyTo, amount);
		cout << "\n\t\t\t\t\t" << amount << " " << clsString::UpperAllString(CurrencyFrom.GetCurrencyCode()) << " = " << ExchangeResult << " " << clsString::UpperAllString(CurrencyTo.GetCurrencyCode()) << endl;
	}

public :

	static void ShowCurrencyCalculator()
	{
		do
		{
			system("cls");
			_DrawScreenHeader("Currency Calculator");

			
			clsCurrency CurrencyFrom = _GetCurrencyByCurrencyCode("Please Enter the Currency from code : ");
			clsCurrency CurrencyTo = _GetCurrencyByCurrencyCode("Please Enter the Currency to code : ");
			

			float amount = _ReadExchangeAmount();
			_PrintExchangeResult(CurrencyFrom, CurrencyTo, amount);

			cout << "\n\t\t\t\t\tDo you want to make an another exchange ? y/n : ";
			bool choice = _ReadYOrN();

			if (!choice)
				break;


		} while (true);
	}

};

