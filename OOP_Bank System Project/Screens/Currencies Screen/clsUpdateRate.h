#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"

class clsUpdateRate : protected clsScreen
{
private :

	static void _Print(clsCurrency Currency)
	{

		cout << "\n\t\t\t\t\tCurrency Card :";
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

public :

	static void UpdateCurrencyRate()
	{
		_DrawScreenHeader("Update Currency Screen");

		string CurrencyCode = clsInputValidate::ReadValidString("\t\t\t\t\tPlease Enter Currency Code : ");

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			string CurrencyCode = clsInputValidate::ReadValidString("\t\t\t\t\tCurrency Code was NOT found.Please Enter another Currency Code : ");
		}

		clsCurrency Currency = clsCurrency::Find(CurrencyCode);
		_Print(Currency);

		cout << "\n\t\t\t\t\tAre you sure you want to update the rate of this Currency y/n ? ";
		bool choice = _ReadYOrN();

		if (choice)
		{
			cout << "\n\t\t\t\t\tUpdating Currency Rate:";
			cout << "\n\t\t\t\t\t_______________________";

			float NewRate = clsInputValidate::ReadNumber<float>("\t\t\t\t\tEnter New Rate : ", "\t\t\t\t\tInvalid input please try again : ");
			Currency.UpdateRate(NewRate);
			cout << "\n\t\t\t\t\tCurrency Rate Updated Successfully !!\n";
			_Print(Currency);
			return;
		}

		cout << "\n\t\t\t\t\tUpdating Currency Rate has been Cancelled ";
	}
};

