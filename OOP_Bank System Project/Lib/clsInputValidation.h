#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{
public:

	template <typename T> static bool IsNumberBetween(T num, T from, T to)
	{
		return num <= to && num >= from;
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		if (clsDate::IsDate1BeforeDate2(DateTo, DateFrom))
			clsDate::SwapDates(DateFrom, DateTo);

		return (clsDate::IsDate1BeforeDate2(Date, DateTo) || clsDate::IsDate1EqualToDate2(Date, DateTo))
			&& (clsDate::IsDate1AfterDate2(Date, DateFrom) || clsDate::IsDate1EqualToDate2(Date, DateTo));
	}

	template <typename T> static T ReadNumber(string ReadMessage, string InvalidMessage)
	{
		T Num = 0;

		cout << "\n" << ReadMessage;
		cin >> Num;

		while (cin.fail())
		{
			cout << "\n" << InvalidMessage;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "\n" << ReadMessage;
			cin >> Num;
		}

		return Num;
	}

	template <typename T> static T ReadNumberBetween(string ReadMessage, string InvalidMessage, T from, T to)
	{
		T Num = ReadNumber<T>(ReadMessage, InvalidMessage);

		while (!IsNumberBetween(Num, from, to))
		{
			cout << "\n" << InvalidMessage;
			Num = ReadNumber<T>(ReadMessage, InvalidMessage);
		}
		return Num;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadValidString(string ReadMessage, short maxLength = 100, short minLength = 1)
	{
		string input;

		do
		{
			cin.clear();
			cout << "\n" << ReadMessage;
			getline(cin >> ws, input);

			if (input.length() > maxLength)
				cout << "\nWrong Input. Please Enter a String with max length : " << maxLength << " Characters \n";

			else if (input.length() < minLength)
				cout << "\nWrong Input. Please Enter a String with min length : " << minLength << " Characters \n";


		} while (cin.fail() || (input.length() > maxLength || input.length() < minLength));

		return input;
	}


};

