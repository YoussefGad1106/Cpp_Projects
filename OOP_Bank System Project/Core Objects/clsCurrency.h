#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
using namespace std;

class clsCurrency
{
private:

	enum enMode { EmptyMode = 1, UpdateMode = 2 };
	enMode _Mode;

	string _CountryName;
	string _CurrencyName;
	string _CurrencyCode;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector<string> vCurrencyData;

		vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		vector <string> vCurrencyData;


		vCurrencyData.push_back(Currency._CountryName);
		vCurrencyData.push_back(Currency._CurrencyCode);
		vCurrencyData.push_back(Currency._CurrencyName);
		vCurrencyData.push_back(to_string(Currency._Rate));


		return clsString::JoinString(vCurrencyData, Separator);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFileToVector()
	{
		vector<clsCurrency> vCurrencies;
		fstream MyFile;
		string Line;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveClientsDataToFile(vector<clsCurrency>& vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				MyFile << _ConvertCurrencyObjectToLine(Currency) << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFileToVector();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.GetCurrencyCode() == this->_CurrencyCode)
			{
				Currency = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vCurrencies);
	}

public:

	clsCurrency(enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_CountryName = CountryName;
		_CurrencyName = CurrencyName;
		_CurrencyCode = CurrencyCode;
		_Rate = Rate;
	}

	string GetCountryName()
	{
		return _CountryName;
	}

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	float GetRate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static bool IsCurrencyExist(string SearchKey)
	{
		return (!Find(SearchKey).IsEmpty());
	}

	static clsCurrency Find(string SearchKey)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFileToVector();

		for (clsCurrency& Currency : vCurrencies)
		{
			if ((clsString::UpperAllString(Currency._CountryName) == clsString::UpperAllString(SearchKey))
				|| (clsString::UpperAllString(Currency._CurrencyCode) == clsString::UpperAllString(SearchKey)))
			{
				return Currency;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFileToVector();
	}

	float ExchangeToUsd(float amount)
	{
		return amount / GetRate();
	}

	float ExchangeTwoCurrencies(clsCurrency CurrencyTo, float amount)
	{
		if (clsString::UpperAllString(CurrencyTo.GetCurrencyCode()) == "USD")
			return ExchangeToUsd(amount);

		return ExchangeToUsd(amount) * CurrencyTo.GetRate();
	}
};

