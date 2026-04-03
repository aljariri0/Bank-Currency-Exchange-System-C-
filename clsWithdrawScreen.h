#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsWithdrawScreen {


public:


	static void ShowWithdrawScreen() {

		cout << "Please Enter an account number: ";
		string account_number = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(account_number)) {

			cout << "\nClient wiht [" << account_number << "] is not exist.\n";
			account_number = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(account_number);

		client.Print();

		cout << "\nPlease Enter Withdraw amount? ";
		double amount = clsInputValidate::ReadDoubleNumber("Invalid number, enter again: ");

		if (amount > client.GetAccountBalance()) {

			cout << "\nYou Can't withdraw more than " << client.GetAccountBalance() << ", Enter another amount: " << endl;
			return;
		}

		char sure = 'n';
		cout << "\nAre you sure you want to perform this transaction y/n ? ";
		cin >> sure;

		if (sure == 'Y' || sure == 'y') {

			client.SetAccountBalance(client.GetAccountBalance() - amount);
			client.Save();

			cout << "\nAmount Withdraw Successfully.\n";
			cout << "\nNew Balance is " << client.GetAccountBalance();
		}

		else {

			cout << "\nOperation was cancelled.\n";
		}
	}
};

