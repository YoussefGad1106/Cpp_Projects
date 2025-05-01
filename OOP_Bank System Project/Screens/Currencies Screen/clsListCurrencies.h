#pragma once
#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

class clsListCurrencies : protected clsScreen
{
private :

	static void _PrintCurrencyObjectData(clsCurrency Currency)
	{
		cout << "| " << setw(35) << left << Currency.GetCountryName();
		cout << "| " << setw(15) << left << Currency.GetCurrencyCode();
		cout << "| " << setw(40) << left << Currency.GetCurrencyName();
		cout << "| " << setw(10) << left << Currency.GetRate();
	}

public :

	static void ShowListCurrenciesScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		_DrawScreenHeader("Currencies List", to_string(vCurrencies.size()) + " Currencies.");
		cout << "\n_______________________________________________________";
		cout << "___________________________________________________________\n" << endl;

		cout << "| " << left << setw(35) << "Country Name";
		cout << "| " << left << setw(15) << "Currency Code";
		cout << "| " << left << setw(40) << "Currency Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << "\n_______________________________________________________";
		cout << "___________________________________________________________\n" << endl;

		if (vCurrencies.empty())
			cout << "\t\t\t  No Currencies Available In the System!";
		else

			for (clsCurrency& Currency : vCurrencies)
			{

				_PrintCurrencyObjectData(Currency);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "___________________________________________________________\n" << endl;
	}
};

