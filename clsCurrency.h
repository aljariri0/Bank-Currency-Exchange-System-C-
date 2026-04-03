#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency {

	enum enMode{ eEmptyMode = 0, eUpdateMode = 1};

	enMode _mode;
	string _country;
	string _currency_name;
	string _currency_code;
	float _rate;

	static clsCurrency _ConvertDatalineToCurrencyObject(string data_line) {

		vector<string> vCurrency = clsString::Split(data_line, "#//#");

		return clsCurrency(enMode::eUpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {

		string data_line = "";
		data_line += Currency.GetCountry() + Seperator;
		data_line += Currency.GetCurrencyCode() + Seperator;
		data_line += Currency.GetCurrencyName() + Seperator;
		data_line += to_string(Currency.GetRate());

		return data_line;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency>& vCurrencys) {

		fstream file;
		file.open("Currencies.txt", ios::out);

		if (file.is_open()) {

			for (clsCurrency& C : vCurrencys) {

				file << _ConvertCurrencyObjectToLine(C) << endl;
			}

			file.close();
		}
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {

		vector <clsCurrency> vAllCurrencies;
		fstream file;

		file.open("Currencies.txt", ios::in);

		if (file.is_open()) {

			string data_line = "";

			while (getline(file, data_line)) {

				if (data_line.empty())
					continue;

				clsCurrency currency = _ConvertDatalineToCurrencyObject(data_line);
				vAllCurrencies.push_back(currency);
			}

			file.close();
		}

		return vAllCurrencies;
	}

	void _Update() {

		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& c : vCurrencies) {

			if (c.GetCurrencyCode() == this->GetCurrencyCode()) {

				c = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencies);
	}

	static void _PrintCurrency(clsCurrency currency) {

		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << currency.GetCountry();
		cout << "\nCode       : " << currency.GetCurrencyCode();
		cout << "\nName       : " << currency.GetCurrencyName();
		cout << "\nRate(1$) = : " << currency.GetRate();

		cout << "\n_____________________________\n";

	}

public:

	clsCurrency(enMode mode, string country, string currency_code,
		string currency_name, float rate) {

		_mode = mode;
		_country = country;
		_currency_name = currency_name;
		_currency_code = currency_code;
		_rate = rate;
	}

	bool IsEmpty() {

		return _mode == enMode::eEmptyMode;
	}

	string GetCurrencyName() {

		return _currency_name;
	}

	string GetCurrencyCode() {

		return _currency_code;
	}

	string GetCountry() {

		return _country;
	}

	float GetRate() {

		return _rate;
	}

	void SetRate(float rate) {

		_rate = rate;
		_Update();
	}

	static clsCurrency FindByCurrencyCode(string currency_code) {

		currency_code = clsString::UpperEachWord(currency_code);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open()) {

			string data_line = "";
			
			while (getline(file, data_line)) {

				if (data_line.empty())
					continue;

				clsCurrency currency = _ConvertDatalineToCurrencyObject(data_line);

				if (currency.GetCurrencyCode() == currency_code) {

					file.close();
					return currency;
				}
			}

			file.close();
		}

		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}

	static clsCurrency FindByCountry(string country) {

		country = clsString::UpperEachWord(country);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open()) {

			string data_line = "";
			
			while (getline(file, data_line)) {

				if (data_line.empty())
					continue;

				clsCurrency currency = _ConvertDatalineToCurrencyObject(data_line);

				if (clsString::UpperEachWord(currency.GetCountry()) == country) {

					file.close();
					return currency;
				}
			}

			file.close();
		}

		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}

	static bool IsCurrencyExist(string currency_code) {

		clsCurrency c = clsCurrency::FindByCurrencyCode(currency_code);

		return (!c.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList() {
		
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float amount) {

		return (float)amount / _rate;
	}

	float ConvertToOtherCurrency(float amount, clsCurrency c2) {

		float amount_in_usd = ConvertToUSD(amount);

		if (c2.GetCurrencyCode() == "USD")
			return amount_in_usd;

		return amount_in_usd * c2.GetRate();
	}
};

