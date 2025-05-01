#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
using namespace std;

class clsFindCurrency : protected clsScreen
{
private:

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

public:

	static void FindCurrency()
	{
		_DrawScreenHeader("Find Currency");

		string SearchKey = clsInputValidate::ReadValidString("\n\t\t\t\t\tPlease Enter Currency Code or Country Name: ");

		clsCurrency Currency = clsCurrency::Find(SearchKey);

		if (Currency.IsEmpty())
		{
			cout << "\n\t\t\t\t\tCurrency NOT found\n";
			return;
		}

		cout << "\n\n\t\t\t\t\tCurrency has been Found\n";
		_Print(Currency);

	}
};

