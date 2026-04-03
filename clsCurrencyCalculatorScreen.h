#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen :protected clsScreen {

private:

    static float _ReadAmount() {
            
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadDoubleNumber("Invalid number, enter again: ");
        return Amount;
    }

    static clsCurrency _GetCurrency(string Message) {

        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        return Currency;
    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.GetCountry();
        cout << "\nCode          : " << Currency.GetCurrencyCode();
        cout << "\nName          : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) =    : " << Currency.GetRate();
        cout << "\n_____________________________\n\n";

    }

    static void _PrintCalculationsResults(float amount, clsCurrency currency_from, clsCurrency currency_to) {

        _PrintCurrencyCard(currency_from, "Convert From:");

        float amount_In_USD = currency_from.ConvertToUSD(amount);

        if (currency_to.GetCurrencyCode() == "USD")
            return;

        _PrintCurrencyCard(currency_to, "To:");

        float amount_in_currrency_from = currency_from.ConvertToOtherCurrency(amount, currency_to);

        cout << amount << " " << currency_from.GetCurrencyCode()
            << " = " << amount_in_currrency_from << " " << currency_to.GetCurrencyCode();
    }


public:

    static void ShowCurrencyCalculatorScreen()
    {
        char continue_flag = 'y';

        while (continue_flag == 'y' || continue_flag == 'Y') {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency Code From: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency Code To: ");

            float amount = _ReadAmount();

            _PrintCalculationsResults(amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> continue_flag;
        }
    }
};

