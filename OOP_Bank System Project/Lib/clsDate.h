#pragma once
#pragma warning (disable : 4996) 
#include <iostream>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate
{
	short _Day, _Month, _Year;

	static int ReadPositiveNumber(string Message)
	{
		int Number = 0;
		do
		{
			cout << "\n" << Message;
			cin >> Number;
		} while (Number <= 0);
		return Number;
	}

public:

	enum enCompare2Dates { Before = -1, Equal = 0, After = 1 };

	clsDate()
	{
		DateToday();
	}

	clsDate(string StringDate)
	{
		StringToDate(StringDate);
	}

	clsDate(short Day, short Month, short Year)
		: _Day(Day), _Month(Month), _Year(Year) {}

	clsDate(short NumberOfDaysFromTheBeginningOfTheYear, short Year)
	{
		*this = DateOfDayOrderInYear(Year, NumberOfDaysFromTheBeginningOfTheYear);
	}

	void SetDay(short Day)
	{
		this->_Day = Day;
	}

	void SetMonth(short Month)
	{
		this->_Month = Month;
	}

	void SetYear(short Year)
	{
		this->_Year = Year;
	}

	short GetDay()
	{
		return _Day;
	}

	short GetMonth()
	{
		return _Month;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = Day, put = SetDay)) short Day;
	__declspec(property(get = Month, put = SetMonth)) short Month;
	__declspec(property(get = Year, put = SetYear)) short Year;

	static bool IsLeapYear(int Year)
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(this->_Year);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(this->_Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}
		short DaysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : DaysInMonth[Month - 1];
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(this->_Month, this->_Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate& Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] =
		{
			"Sun","Mon","Tue","Wed","Thu","Fri","Sat"
		};

		return arrDayNames[DayOfWeekOrder];
	}

	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[13] =
		{ "", "Jan", "Feb", "Mar",
			"Apr", "May", "Jun",
			"Jul", "Aug", "Sep",
			"Oct", "Nov", "Dec"
		};
		return Months[MonthNumber];
	}

	string MonthShortName()
	{
		return MonthShortName(this->_Month);
	}

	static void PrintMonthHeader(short Month)
	{
		printf("\n _______________%s_______________\n\n", MonthShortName(Month).c_str());

		printf(" Sun Mon Tue Wed Thu Fri Sat\n");
	}

	void PrintMonthHeader()
	{
		PrintMonthHeader(this->_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		short NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		short current = DayOfWeekOrder(1, Month, Year);

		PrintMonthHeader(Month);

		int i;

		// to assign the first day of the month in its suitable place
		for (i = 0; i < current; i++)
			printf("    ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%4d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n"); // to move to the next row
			}
		}
		printf("\n _________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(this->_Month, this->_Year);
	}

	static short NumberOfDaysFromTheBeginningOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}

	short NumberOfDaysFromTheBeginningOfTheYear()
	{
		return NumberOfDaysFromTheBeginningOfTheYear(*this);
	}

	static clsDate DateOfDayOrderInYear(short Year, short NumberOfDays)
	{
		clsDate Date;
		Date._Year = Year;

		short Month = 0, Day = 0, TotalDays = 0, MonthDays = 0;

		for (int i = 1; i < 13; i++)
		{
			MonthDays = NumberOfDaysInAMonth(i, Year);
			TotalDays += MonthDays;

			if (TotalDays > NumberOfDays)
			{
				Date._Month = i;
				Date._Day = NumberOfDays - (TotalDays - MonthDays);
				break;
			}

		}

		return Date;
	}

	static bool IsDayLastDayInMonth(clsDate Date)
	{
		return Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year);
	}

	bool IsDayLastDayInMonth()
	{
		return IsDayLastDayInMonth(*this);
	}

	static bool IsMonthLastMonthInYear(clsDate Date)
	{
		return Date._Month == 12;
	}

	bool IsMonthLastMonthInYear()
	{
		return IsMonthLastMonthInYear(*this);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true
			: (NumberOfDaysFromTheBeginningOfTheYear(Date1._Day, Date1._Month, Date1._Year)) < NumberOfDaysFromTheBeginningOfTheYear(Date2._Day, Date2._Month, Date2._Year);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2)
	{
		return NumberOfDaysFromTheBeginningOfTheYear(Date1._Day, Date1._Month, Date1._Year) == NumberOfDaysFromTheBeginningOfTheYear(Date2._Day, Date2._Month, Date2._Year);
	}

	bool IsDateEqualToDate2(clsDate Date2)
	{
		return IsDate1EqualToDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2);
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static int CalculateYearsDifferenceOf2Dates(clsDate Date1, clsDate Date2)
	{
		int Difference = 0;

		while (Date1._Year != Date2._Year)
		{
			Difference += NumberOfDaysInYear(Date1._Year);
			Date1._Year++;
		}

		return Difference;
	}

	int CalculateYearsDifferenceOf2Dates(clsDate Date2)
	{
		return CalculateYearsDifferenceOf2Dates(*this, Date2);
	}

	static int CalculateMonthsDifferenceOf2Dates(clsDate Date1, clsDate Date2)
	{
		int Difference = 0;

		while (Date1._Month != Date2._Month)
		{
			Difference += NumberOfDaysInAMonth(Date1._Month, Date1._Year);
			Date1._Month++;

			if (Date1._Month == 13)
			{
				Date1._Month = 1;
				Date1._Year++;
			}
		}

		return Difference;
	}

	int CalculateMonthsDifferenceOf2Dates(clsDate Date2)
	{
		return CalculateMonthsDifferenceOf2Dates(*this, Date2);
	}

	static int CalculateDifferenceOf2Dates(clsDate Date1, clsDate Date2, bool IncludingEndDay = false)
	{
		int Difference = 0;

		if (!IsDate1BeforeDate2(Date1, Date2))
			return (-1) * CalculateDifferenceOf2Dates(Date2, Date1, IncludingEndDay);

		Difference += CalculateYearsDifferenceOf2Dates(Date1, Date2);
		Difference += CalculateMonthsDifferenceOf2Dates(Date1, Date2);


		if (IncludingEndDay)
			Difference += (Date2._Day - Date1._Day + 1);
		else
			Difference += (Date2._Day - Date1._Day);

		return Difference;
	}

	int CalculateDifferenceOf2Dates(clsDate Date2, bool IncludingEndDay = false)
	{
		return CalculateDifferenceOf2Dates(*this, Date2, IncludingEndDay);
	}

	static void IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsDayLastDayInMonth(Date))
		{
			if (IsMonthLastMonthInYear(Date))
			{
				Date._Day = Date._Month = 1;
				Date._Year++;
				return;
			}

			Date._Day = 1;
			Date._Month++;
		}
		else
			Date._Day++;

	}

	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static void IncreaseDateByXDays(clsDate& Date, short Days)
	{
		for (short i = 0; i < Days; i++)
			IncreaseDateByOneDay(Date);
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}

	static void IncreaseDateByOneWeek(clsDate& Date)
	{
		IncreaseDateByXDays(Date, 7);
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static void IncreaseDateByXWeeks(clsDate& Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			IncreaseDateByOneWeek(Date);
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static void IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsMonthLastMonthInYear(Date))
		{
			Date._Month = 1;
			Date._Year++;
			return;
		}

		Date._Month++;
		short NumberOfDaysInThisMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		// Handling the Number of Days exceed the number of days in the current month

		if (Date._Day > NumberOfDaysInThisMonth)
			Date._Day = NumberOfDaysInThisMonth;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static void IncreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (short i = 0; i < Months; i++)
		{
			IncreaseDateByOneMonth(Date);
		}
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}

	static void IncreaseDateByOneYear(clsDate& Date)
	{
		if (!IsLeapYear(Date._Year + 1) && (Date._Month == 2 && Date._Day == 29))
		{
			Date._Year++;
			Date._Month = 3;
			Date._Day = 1;
			return;
		}
		Date._Year++;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static void IncreaseDateByXYears(clsDate& Date, short Years)
	{
		if (!IsLeapYear(Date._Year + 1) && (Date._Month == 2 && Date._Day == 29))
		{
			Date._Year += Years;
			Date._Month = 3;
			Date._Day = 1;
			return;
		}
		Date._Year += Years;

	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}

	static void IncreaseDateByOneDecade(clsDate& Date)
	{
		IncreaseDateByXYears(Date, 10);
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static void IncreaseDateByXDecades(clsDate& Date, short Decades)
	{
		IncreaseDateByXYears(Date, Decades * 10);
	}

	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}

	static void IncreaseDateByOneCentury(clsDate& Date)
	{
		IncreaseDateByXYears(Date, 100);
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static void IncreaseDateByOneMillennium(clsDate& Date)
	{
		IncreaseDateByXYears(Date, 1000);
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static bool IsDayFirstDayInMonth(clsDate& Date)
	{
		return Date._Day == 1;
	}

	bool IsDayFirstDayInMonth()
	{
		IsDayFirstDayInMonth(*this);
	}

	static bool IsMonthFirstMonthInYear(clsDate& Date)
	{
		return Date._Month == 1;
	}

	bool IsMonthFirstMonthInYear()
	{
		IsMonthFirstMonthInYear(*this);
	}

	static void DecreaseDateByOneDay(clsDate& Date)
	{
		if (IsDayFirstDayInMonth(Date))
		{
			if (IsMonthFirstMonthInYear(Date))
			{
				Date._Month = 12;
				Date._Year--;
				Date._Day = 31;
				return;
			}

			Date._Month--;
			Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
		}
		else
			Date._Day--;

	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static void DecreaseDateByXDays(clsDate& Date, short Days)
	{
		for (short i = 0; i < Days; i++)
			DecreaseDateByOneDay(Date);
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}

	static void DecreaseDateByOneWeek(clsDate& Date)
	{
		DecreaseDateByXDays(Date, 7);
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static void DecreaseDateByXWeeks(clsDate& Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			DecreaseDateByOneWeek(Date);
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(*this, Weeks);
	}

	static void DecreaseDateByOneMonth(clsDate& Date)
	{
		if (IsMonthFirstMonthInYear(Date))
		{
			Date._Month = 12;
			Date._Year--;
			return;
		}

		Date._Month--;
		short NumberOfDaysInThisMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		// Handling the Number of Days exceed the number of days in the current month

		if (Date._Day > NumberOfDaysInThisMonth)
			Date._Day = NumberOfDaysInThisMonth;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static void DecreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (short i = 0; i < Months; i++)
		{
			DecreaseDateByOneMonth(Date);
		}
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(*this, Months);
	}

	static void DecreaseDateByOneYear(clsDate& Date)
	{
		if (!IsLeapYear(Date._Year - 1) && (Date._Month == 2 && Date._Day == 29))
		{
			Date._Year--;
			Date._Month = 3;
			Date._Day = 1;
			return;
		}
		Date._Year--;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static void DecreaseDateByXYears(clsDate& Date, short Years)
	{
		if (!IsLeapYear(Date._Year - 1) && (Date._Month == 2 && Date._Day == 29))
		{
			Date._Year -= Years;
			Date._Month = 3;
			Date._Day = 1;
			return;
		}
		Date._Year -= Years;

	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(*this, Years);
	}

	static void DecreaseDateByOneDecade(clsDate& Date)
	{
		DecreaseDateByXYears(Date, 10);
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static void DecreaseDateByXDecades(clsDate& Date, short Decades)
	{
		DecreaseDateByXYears(Date, Decades * 10);
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(*this, Decades);
	}

	static void DecreaseDateByOneCentury(clsDate& Date)
	{
		DecreaseDateByXYears(Date, 100);
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static void DecreaseDateByOneMillennium(clsDate& Date)
	{
		DecreaseDateByXYears(Date, 1000);
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	short NumberOfDaysFromTheBeginningOfTheYear(clsDate& Date)
	{
		return NumberOfDaysFromTheBeginningOfTheYear(Date._Day, Date._Month, Date._Year);
	}

	static bool IsEndOfWeek(clsDate& Date)
	{
		return  DayOfWeekOrder(Date) == 6;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate& Date)
	{
		return DayOfWeekOrder(Date) == 5 || DayOfWeekOrder(Date) == 6;
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate& Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfTheWeek(clsDate& Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfTheWeek()
	{
		return DaysUntilTheEndOfTheWeek(*this);
	}

	static short DaysUntilTheEndOfTheMonth(clsDate& Date)
	{
		return NumberOfDaysInAMonth(Date._Month, Date._Year) - Date._Day;
	}

	short DaysUntilTheEndOfTheMonth()
	{
		DaysUntilTheEndOfTheMonth(*this);
	}

	static short DaysUntilTheEndOfTheYear(clsDate& Date)
	{
		return NumberOfDaysInYear(Date._Year) - NumberOfDaysFromTheBeginningOfTheYear(Date._Day, Date._Month, Date._Year);
	}

	short DaysUntilTheEndOfTheYear()
	{
		DaysUntilTheEndOfTheYear(*this);
	}

	static void PrintDate(clsDate Date)
	{
		cout << "Date : " << Date._Day << "/" << Date._Month << "/" << Date._Year << endl;
	}

	void PrintDate()
	{
		PrintDate(*this);
	}

	static enCompare2Dates Compare2Dates(clsDate Date1, clsDate Date2)
	{
		enCompare2Dates result;

		result = IsDate1AfterDate2(Date1, Date2) ? enCompare2Dates::After :
			IsDate1BeforeDate2(Date1, Date2) ? enCompare2Dates::Before : enCompare2Dates::Equal;

		return result;
	}

	enCompare2Dates Compare2Dates(clsDate Date2)
	{
		Compare2Dates(*this, Date2);
	}

	static clsDate ReadDate()
	{
		clsDate Date;

		Date._Day = ReadPositiveNumber("Enter a Day : ");
		Date._Month = ReadPositiveNumber("Enter a Month : ");
		Date._Year = ReadPositiveNumber("Enter a Year : ");
		cout << endl;

		return Date;
	}

	static bool IsValidDate(clsDate Date)
	{
		return (Date._Day > 0 && Date._Day <= NumberOfDaysInAMonth(Date._Month, Date._Year)) && (Date._Month > 0 && Date._Month < 13);
	}

	bool IsValidDate()
	{
		IsValidDate(*this);
	}

	static void DateToday(clsDate& Date)
	{

		time_t t = time(0);
		tm* timeStruct = localtime(&t);

		Date._Day = timeStruct->tm_mday;
		Date._Month = timeStruct->tm_mon + 1;
		Date._Year = timeStruct->tm_year + 1900;

	}

	static string TimeNow()
	{
		time_t t = time(0);
		tm* timeStruct = localtime(&t);

		return to_string(timeStruct->tm_hour) + ':' + to_string(timeStruct->tm_min) + ':' + to_string(timeStruct->tm_sec);
	}

	static string DateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short sec, min, hr, day, month, year;

		sec = now->tm_sec;
		min = now->tm_min;
		hr = now->tm_hour;
		day = now->tm_mday;
		month = now->tm_mon + 1;
		year = now->tm_year + 1900;

		return to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " - "
			  + to_string(hr) + ":" + to_string(min) + ":" + to_string(sec);
	}

	void DateToday()
	{
		DateToday(*this);
	}

	static void StringToDate(clsDate& Date, string strDate)
	{
		vector<string> dateStringVector = clsString::Split(strDate, "/");

		Date._Day = stoi(dateStringVector[0]);
		Date._Month = stoi(dateStringVector[1]);
		Date._Year = stoi(dateStringVector[2]);

	}

	void StringToDate(string strDate)
	{
		StringToDate(*this, strDate);
	}

	static string DateToString(clsDate Date, string Delim = "/")
	{
		return to_string(Date._Day) + Delim + to_string(Date._Month) + Delim + to_string(Date._Year);
	}

	string DateToString(string Delim = "/")
	{
		return DateToString(*this, Delim);
	}

	static string ChangeDateFormat(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";

		FormattedDateString = clsString::ReplaceWord(DateFormat, "dd", to_string(Date._Day));
		FormattedDateString = clsString::ReplaceWord(FormattedDateString, "mm", to_string(Date._Month));
		FormattedDateString = clsString::ReplaceWord(FormattedDateString, "yyyy", to_string(Date._Year));

		return FormattedDateString;
	}

	string ChangeDateFormat(string DateFormat = "dd/mm/yyyy")
	{
		ChangeDateFormat(*this, DateFormat);
	}

	static void  SwapDates(clsDate& Date1, clsDate& Date2)
	{

		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;

	}

	static short DaysUntilTheEndOfYear(clsDate Date1)
	{

		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date1._Year;

		return CalculateDifferenceOf2Dates(Date1, EndOfYearDate, true);

	}

};

