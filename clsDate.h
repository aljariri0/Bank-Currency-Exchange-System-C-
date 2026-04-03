#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsDate
{

private:

	int _day;
	int _month;
	int _year;

public:

	clsDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		_day = now->tm_mday;
		_month = now->tm_mon + 1;
		_year = now->tm_year + 1900;
	}

	clsDate(string date) {

		vector <string> vDate;
		vDate = clsString::Split(date, "/");

		_day = stoi(vDate[0]);
		_month = stoi(vDate[1]);
		_year = stoi(vDate[2]);
	}

	clsDate(int day, int month, int year) {

		_day = day;
		_month = month;
		_year = year;

	}

	clsDate(int days, int year)
	{

		clsDate date = GetDateFromDayOrderInYear(days, year);

		_day = date.day;
		_month = date.month;
		_year = date.year;
	}

	void Setday(int day) {

		_day = day;
	}

	int Getday() {

		return _day;
	}

	__declspec(property(get = Getday, put = Setday)) int day;

	
	void Setmonth(int month) {

		_month = month;
	}

	int Getmonth() {

		return _month;
	}

	__declspec(property(get = Getmonth, put = Setmonth)) int month;

	
	void Setyear(int year) {

		_year = year;
	}

	int Getyear() {

		return _year;
	}

	__declspec(property(get = Getyear, put = Setyear)) int year;


	void Print()
	{
		cout << DateToString() << endl;
	}


	static clsDate GetSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		return clsDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}

	static string GetSystemTime() {

		time_t t = time(0);
		tm* now = localtime(&t);

		string time_now = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);

		return time_now;
	}

	static clsDate GetFullSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		return clsDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}


	bool IsLeapyear() {

		return ((_year % 4 == 0 && _year % 100 != 0) || _year % 400 == 0);
	}

	static bool IsLeapyear(int year) {

		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}




	static int NumberOfdaysInmonth(int month, int year) {


		switch (month) {

		case 1:
			return 31;

		case 2:

			return (IsLeapyear(year) ? 29 : 28);

		case 3:
			return 31;

		case 4:
			return 30;

		case 5:
			return 31;

		case 6:
			return 30;

		case 7:
			return 31;

		case 8:
			return 31;

		case 9:
			return 30;

		case 10:
			return 31;

		case 11:
			return 30;

		case 12:
			return 31;
		}
	}

	int NumberOfdaysInmonth() {

		return NumberOfdaysInmonth(_month, _year);
	}




	static bool IsValidDate(clsDate date) {

		if (date.day < 1 || date.day > NumberOfdaysInmonth(date.month, date.year)) {

			return false;
		}

		if (date.month < 1 || date.month > 12)
			return false;

		if (date.month == 2) {

			if (IsLeapyear(date.year)) {

				if (date.day > 29)
					return false;
			}

			else if(date.day > 28)
				return false;
		}

		return true;
	}

	bool IsValid() {

		return IsValidDate(*this);
	}



	static string DateToString(clsDate date) {

		return  to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}

	string DateToString() {

		return DateToString(*this);
	}



	static short NumberOfdaysInAyear(short year)
	{
		return IsLeapyear(year) ? 365 : 364;
	}

	short NumberOfdaysInAyear()
	{
		return  IsLeapyear(_year);
	}



	static short NumberOfHoursInAyear(short year) {

		return NumberOfdaysInAyear(year) * 24;
	}

	short NumberOfHoursInAyear() {

		return NumberOfHoursInAyear(_year);
	}

	static int NumberOfMinutesInAyear(short year) {

		return NumberOfHoursInAyear(year) * 60;
	}

	int NumberOfMinutesInAyear() {

		return NumberOfMinutesInAyear(_year);
	}

	static int NumberOfSecondsInAyear(short year) {

		return NumberOfMinutesInAyear(year) * 60;
	}

	int NumberOfSecondsInAyear() {

		return NumberOfSecondsInAyear(_year);
	}



	static short NumberOfHoursInAmonth(short month, short year)
	{
		return NumberOfdaysInmonth(month, year) * 24;
	}

	short NumberOfHoursInAmonth()
	{
		return NumberOfdaysInmonth(_month, _year) * 24;
	}


	static int NumberOfMinutesInAmonth(short month, short year)
	{
		return NumberOfHoursInAmonth(month, year) * 60;
	}


	static int NumberOfSecondsInAmonth(short month, short year) {

		return  NumberOfMinutesInAmonth(month, year) * 60;
	}

	int NumberOfSecondsInAmonth() {

		return  NumberOfMinutesInAmonth(_month, _year) * 60;
	}

	int NumberOfMinutesInAmonth() {

		return NumberOfHoursInAmonth(_month, _year) * 60;
	}



	static short dayOfWeekOrder(short day, short month, short year)
	{
		short a, y, m;
		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc

		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short dayOfWeekOrder()
	{
		return dayOfWeekOrder(_day, _month, _year);
	}




	static string dayShortName(short dayOfWeekOrder)
	{
		string arrdayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrdayNames[dayOfWeekOrder];

	}

	static string dayShortName(short day, short month, short year)
	{

		string arrdayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrdayNames[dayOfWeekOrder(day, month, year)];

	}

	string dayShortName()
	{

		string arrdayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrdayNames[dayOfWeekOrder(_day, _month, _year)];

	}

	static string monthShortName(short monthNumber)
	{
		string months[12] = { "Jan", "Feb", "Mar",
						   "Apr", "May", "Jun",
						   "Jul", "Aug", "Sep",
						   "Oct", "Nov", "Dec"
		};

		return (months[monthNumber - 1]);
	}

	string monthShortName()
	{

		return monthShortName(_month);
	}



	static void PrintmonthCalendar(short month, short year)
	{
		int NumberOfdays;

		// Index of the day from 0 to 6
		int current = dayOfWeekOrder(1, month, year);

		NumberOfdays = NumberOfdaysInmonth(month, year);

		// Print the current month name
		printf("\n  _______________%s_______________\n\n",
			monthShortName(month).c_str());

		// Print the columns
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfdays; j++)
		{
			printf("%5d", j);


			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");

	}

	void PrintmonthCalendar()
	{
		PrintmonthCalendar(_month, _year);
	}

	static void PrintyearCalendar(int year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", year);
		printf("  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintmonthCalendar(i, year);
		}

		return;
	}

	void PrintyearCalendar()
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", _year);
		printf("  _________________________________\n");


		for (int i = 1; i <= 12; i++)
		{
			PrintmonthCalendar(i, _year);
		}

		return;
	}

	static short daysFromTheBeginingOfTheyear(short day, short month, short year)
	{

		short Totaldays = 0;

		for (int i = 1; i <= month - 1; i++)
		{
			Totaldays += NumberOfdaysInmonth(i, year);
		}

		Totaldays += day;

		return Totaldays;
	}

	short daysFromTheBeginingOfTheyear()
	{

		short Totaldays = 0;

		for (int i = 1; i <= _month - 1; i++)
		{
			Totaldays += NumberOfdaysInmonth(i, _year);
		}

		Totaldays += _day;

		return Totaldays;
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInyear, short year)
	{

		clsDate Date;
		short Remainingdays = DateOrderInyear;
		short monthdays = 0;

		Date.year = year;
		Date.month = 1;

		while (true)
		{
			monthdays = NumberOfdaysInmonth(Date.month, year);

			if (Remainingdays > monthdays)
			{
				Remainingdays -= monthdays;
				Date.month++;
			}
			else
			{
				Date.day = Remainingdays;
				break;
			}

		}

		return Date;
	}

	void Adddays(short days)
	{


		short Remainingdays = days + daysFromTheBeginingOfTheyear(_day, _month, _year);
		short monthdays = 0;

		_month = 1;

		while (true)
		{
			monthdays = NumberOfdaysInmonth(_month, _year);

			if (Remainingdays > monthdays)
			{
				Remainingdays -= monthdays;
				_month++;

				if (_month > 12)
				{
					_month = 1;
					_year++;

				}
			}
			else
			{
				_day = Remainingdays;
				break;
			}

		}


	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return  (Date1.year < Date2.year) ? true : ((Date1.year == Date2.year) ? (Date1.month < Date2.month ? true : (Date1.month == Date2.month ? Date1.day < Date2.day : false)) : false);
	}



	bool IsDateBeforeDate2(clsDate Date2) {

		//  *this sends the current object :-) 
		return  IsDate1BeforeDate2(*this, Date2);
	}




	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return  (Date1.year == Date2.year) ? ((Date1.month == Date2.month) ? ((Date1.day == Date2.day) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		return  IsDate1EqualDate2(*this, Date2);
	}




	static bool IsLastdayInmonth(clsDate Date)
	{

		return (Date.day == NumberOfdaysInmonth(Date.month, Date.year));

	}

	bool IsLastdayInmonth() {

		return IsLastdayInmonth(*this);
	}

	static bool IsLastmonthInyear(short month) {

		return (month == 12);
	}



	static clsDate AddOneday(clsDate Date) {


		if (IsLastdayInmonth(Date)) {

			if (IsLastmonthInyear(Date.month)) {

				Date.month = 1;
				Date.day = 1;
				Date.year++;
			}

			else
			{
				Date.day = 1;
				Date.month++;
			}
		}

		else {

			Date.day++;
		}

		return Date;
	}

	void AddOneday() {

		*this = AddOneday(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {

		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceIndays(clsDate Date1, clsDate Date2, bool IncludeEndday = false) {
		
		int days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {
			
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;

		}

		while (IsDate1BeforeDate2(Date1, Date2)) {

			days++;
			Date1 = AddOneday(Date1);
		}

		return IncludeEndday ? ++days * SawpFlagValue : days * SawpFlagValue;
	}

	int GetDifferenceIndays(clsDate Date2, bool IncludeEndday = false) {

		return GetDifferenceIndays(*this, Date2, IncludeEndday);
	}



	static short CalculateMyAgeIndays(clsDate DateOfBirth) {

		return GetDifferenceIndays(DateOfBirth, clsDate::GetSystemDate(), true);
	}


	static clsDate IncreaseDateByOneWeek(clsDate& Date) {

		for (int i = 1; i <= 7; i++) {

			Date = AddOneday(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek() {

		IncreaseDateByOneWeek(*this);
	}

	clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date) {

		for (short i = 1; i <= Weeks; i++){

			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks) {

		IncreaseDateByXWeeks(Weeks, *this);
	}

	clsDate IncreaseDateByOnemonth(clsDate& Date) {

		if (Date.month == 12) {

			Date.month = 1;
			Date.year++;
		}

		else {
			Date.month++;
		}

		//last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
		// be 28/2/2022
		short NumberOfdaysInCurrentmonth = NumberOfdaysInmonth(Date.month, Date.year);
		if (Date.day > NumberOfdaysInCurrentmonth) {

			Date.day = NumberOfdaysInCurrentmonth;
		}

		return Date;
	}

	void IncreaseDateByOnemonth() {

		IncreaseDateByOnemonth(*this);

	}

	clsDate IncreaseDateByXdays(short days, clsDate& Date) {

		for (short i = 1; i <= days; i++) {

			Date = AddOneday(Date);
		}

		return Date;
	}

	void IncreaseDateByXdays(short days) {

		IncreaseDateByXdays(days, *this);
	}

	clsDate IncreaseDateByXmonths(short months, clsDate& Date) {


		for (short i = 1; i <= months; i++) {

			Date = IncreaseDateByOnemonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXmonths(short months) {

		IncreaseDateByXmonths(months, *this);
	}

	static clsDate IncreaseDateByOneyear(clsDate& Date) {

		Date.year++;
		return Date;
	}

	void IncreaseDateByOneyear() {

		IncreaseDateByOneyear(*this);
	}

	clsDate IncreaseDateByXyears(short years, clsDate& Date) {

		Date.year += years;
		return Date;
	}

	void IncreaseDateByXyears(short years) {

		IncreaseDateByXyears(years);
	}

	clsDate IncreaseDateByOneDecade(clsDate& Date) {

		//Period of 10 years
		Date.year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade() {

		IncreaseDateByOneDecade(*this);
	}

	clsDate IncreaseDateByXDecades(short Decade, clsDate& Date) {

		Date.year += Decade * 10;
		return Date;
	}

	void IncreaseDateByXDecades(short Decade) {

		IncreaseDateByXDecades(Decade, *this);
	}

	clsDate IncreaseDateByOneCentury(clsDate& Date) {

		//Period of 100 years
		Date.year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury() {

		IncreaseDateByOneCentury(*this);
	}

	clsDate IncreaseDateByOneMillennium(clsDate& Date) {

		//Period of 1000 years
		Date.year += 1000;
		return Date;
	}

	clsDate IncreaseDateByOneMillennium() {

		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneday(clsDate Date) {
		if (Date.day == 1)
		{
			if (Date.month == 1) {

				Date.month = 12;
				Date.day = 31;
				Date.year--;
			}

			else {

				Date.month--;
				Date.day = NumberOfdaysInmonth(Date.month, Date.year);
			}
		}

		else {
			Date.day--;
		}

		return Date;
	}

	void DecreaseDateByOneday() {

		DecreaseDateByOneday(*this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {

		for (int i = 1; i <= 7; i++) {

			Date = DecreaseDateByOneday(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek() {

		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date) {

		for (short i = 1; i <= Weeks; i++) {

			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks) { 

		DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOnemonth(clsDate& Date) {

		if (Date.month == 1) {

			Date.month = 12;
			Date.year--;
		}
		else
			Date.month--;


	// last check day in date should not exceed max days in the current month
	// example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
	// be 28/2/2022
		
		short NumberOfdaysInCurrentmonth = NumberOfdaysInmonth(Date.month, Date.year);
		
		if (Date.day > NumberOfdaysInCurrentmonth){

			Date.day = NumberOfdaysInCurrentmonth;
		}


		return Date;
	}

	void DecreaseDateByOnemonth() {

		DecreaseDateByOnemonth(*this);
	}

	static clsDate DecreaseDateByXdays(short days, clsDate& Date) {

		for (short i = 1; i <= days; i++) {

			Date = DecreaseDateByOneday(Date);
		}
		return Date;
	}

	void DecreaseDateByXdays(short days) {

		DecreaseDateByXdays(days, *this);
	}

	static clsDate DecreaseDateByXmonths(short months, clsDate& Date) {

		for (short i = 1; i <= months; i++) {

			Date = DecreaseDateByOnemonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXmonths(short months) {

		DecreaseDateByXmonths(months, *this);
	}

	static clsDate DecreaseDateByOneyear(clsDate& Date) {

		Date.year--;
		return Date;
	}

	void DecreaseDateByOneyear() {

		DecreaseDateByOneyear(*this);
	}

	static clsDate DecreaseDateByXyears(short years, clsDate& Date) {

		Date.year -= years;
		return Date;
	}

	void DecreaseDateByXyears(short years) {

		DecreaseDateByXyears(years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {

		//Period of 10 years
		Date.year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade() {

		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date) {


		Date.year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecades(short Decades) {

		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {

		//Period of 100 years
		Date.year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury() {

		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {

		//Period of 1000 years
		Date.year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium() {

		DecreaseDateByOneMillennium(*this);
	}


	static short IsEndOfWeek(clsDate Date) {

		return  dayOfWeekOrder(Date.day, Date.month, Date.year) == 6;
	}

	short IsEndOfWeek() {

		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {

		//Weekends are Fri and Sat

		short dayIndex = dayOfWeekOrder(Date.day, Date.month, Date.year);
		return  (dayIndex == 5 || dayIndex == 6);
	}

	bool IsWeekEnd() {

		return  IsWeekEnd(*this);
	}

	static bool IsBusinessday(clsDate Date) {

		//Weekends are Sun,Mon,Tue,Wed and Thur

	   /*
		short dayIndex = dayOfWeekOrder(Date.day, Date.month, Date.year);
		return  (dayIndex >= 5 && dayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);

	}

	bool IsBusinessday() {

		return  IsBusinessday(*this);
	}



	static short daysUntilTheEndOfWeek(clsDate Date) {

		return 6 - dayOfWeekOrder(Date.day, Date.month, Date.year);
	}



	short daysUntilTheEndOfWeek() {

		return  daysUntilTheEndOfWeek(*this);
	}



	static short daysUntilTheEndOfmonth(clsDate Date1) {

		clsDate EndOfMonthtDate;
		EndOfMonthtDate.day = NumberOfdaysInmonth(Date1.month, Date1.year);
		EndOfMonthtDate.month = Date1.month;
		EndOfMonthtDate.year = Date1.year;

		return GetDifferenceIndays(Date1, EndOfMonthtDate, true);
	}

	short daysUntilTheEndOfmonth() {

		return daysUntilTheEndOfmonth(*this);
	}



	static short DaysUntilTheEndOfyear(clsDate Date1) {

		clsDate EndOfyearDate;
		EndOfyearDate.day = 31;
		EndOfyearDate.month = 12;
		EndOfyearDate.year = Date1.year;

		return GetDifferenceIndays(Date1, EndOfyearDate, true);

	}

	short DaysUntilTheEndOfyear() {

		return  DaysUntilTheEndOfyear(*this);
	}

	//i added this method to calculate business days between 2 days
	static short CalculateBusinessdays(clsDate DateFrom, clsDate DateTo) {

		short days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessday(DateFrom))
				days++;

			DateFrom = AddOneday(DateFrom);
		}

		return days;

	}

	static short CalculateVacationdays(clsDate DateFrom, clsDate DateTo) {

		/*short days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessday(DateFrom))
				days++;

			DateFrom = AddOneday(DateFrom);
		}*/

		return CalculateBusinessdays(DateFrom, DateTo);

	}
	//above method is eough , no need to have method for the object

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short Vacationdays) {

		short WeekEndCounter = 0;

		for (short i = 1; i <= Vacationdays; i++) {

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneday(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneday(DateFrom);

		return DateFrom;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2){

		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2) {

		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {

		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/


		return enDateCompare::After;

	}

	enDateCompare CompareDates(clsDate Date2) {

		return CompareDates(*this, Date2);
	}
};
