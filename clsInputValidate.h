#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{

public:

	static bool IsNumberBetween(int n, int a, int b) {

		if (n >= a && n <= b) {

			return true;
		}

		return false;
	}

	static bool IsNumberBetween(double n, double a, double b) {

		if (n >= a && n <= b) {

			return true;
		}

		return false;
	}

	static bool IsDateBetween(clsDate date, clsDate a, clsDate b) {

		if (clsDate::IsDate1BeforeDate2(date, b) && clsDate::IsDate1AfterDate2(date, a)) {

			return true;
		}

		return false;
	}

	static int ReadIntNumber(string message) {

		int number;
		cin >> number;

		while (cin.fail()) {

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
			cout << "\n" << message;
			cin >> number;
		}

		return number;
	}

	static double ReadDoubleNumber(string message) {

		double number;
		cin >> number;

		while (cin.fail()) {

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "\n" << message;
			cin >> number;
		}

		return number;
	}

	static string ReadString() {

		string s = "";
		getline(cin >> ws, s);

		return s;
	}

	static int ReadIntegerBetween(int a, int b) {

		int number;
		cout << "Enter an Integer number between " << a << " and " << b << " : ";
		number  = ReadIntNumber("Invalid number, Enter again: ");

		while (number < a || number > b) {

			cout << "\nInvalid Integer, Enter again: ";
			number = ReadIntNumber("Invalid number, Enter again: ");
		}

		return number;
	}

	static double ReadDoubleBetween(double a, double b) {
		
		double number;
		cout << "\nEnter an Integer number between " << a << " and " << b << " : ";
		number = ReadDoubleNumber("Invalid number, Enter again: ");

		while (number < a || number > b) {

			cout << "\nInvalid Integer, Enter again: ";
			number = ReadDoubleNumber("Invalid number, Enter again: ");
		}

		return number;
	}


	static bool IsValideDate(clsDate date) {

		return clsDate::IsValidDate(date);
	}
};

