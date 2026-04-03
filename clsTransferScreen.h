#pragma once
#include <iostream>
#include <fstream>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepsitScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "Globel.h"

using namespace std;
class clsTransferScreen : protected clsScreen {

	static void _PrintMiniClientCard(clsBankClient client) {

		cout << "\nClient Card: \n---------------\n";
		cout << "Full Name   : " << client.GetFirstName() + " " + client.GetLastName() << endl;
		cout << "Acc. Number : " << client.GetAccountNumber() << endl;
		cout << "Balance     : " << client.GetAccountBalance() << endl;
		cout << "---------------\n";
	}

	static void _TransferLog(clsBankClient& from_client, clsBankClient& to_client, double amount, string delimiter = "##") {

		fstream file;
		file.open("TrasferLog.txt", ios::out | ios::app);

		if (file.is_open()) {

			file << clsDate::DateToString(clsDate::GetSystemDate()) << " - " << clsDate::GetSystemTime() << delimiter
				<< from_client.GetAccountNumber() << delimiter << to_client.GetAccountNumber() << delimiter << amount
				<< delimiter << from_client.GetAccountBalance() << delimiter << to_client.GetAccountBalance() << delimiter << GlobelUser::CurrentUser.GetUsername() << endl;


			file.close();
		}
	}

public:

	static void ShowTransferScreen() {

		clsScreen::_DrawScreenHeader("\t  Transfer Screen");

		cout << "\nPlease Enter Account Number To Transfer From: ";
		string account_number = clsInputValidate::ReadString();

		clsBankClient FromClient = clsBankClient::Find(account_number);

		while (!FromClient.IsClientExist(account_number)) {

			cout << "\nThis account number does not Exist, Please Enter Account Number Again: ";
			account_number = clsInputValidate::ReadString();
		}

		_PrintMiniClientCard(FromClient);

		cout << "\nPlease Enter Account Number To Transfer To: ";
		account_number = clsInputValidate::ReadString();

		clsBankClient ToClient = clsBankClient::Find(account_number);

		while (!ToClient.IsClientExist(account_number)) {

			cout << "\nThis account number does not Exist, Please Enter Account Number Again: ";
			account_number = clsInputValidate::ReadString();
		}

		_PrintMiniClientCard(ToClient);

		cout << "\nEnter Transfer Amount: ";
		double amount = clsInputValidate::ReadDoubleNumber("Invalid number, Enter again: ");

		if (amount > FromClient.GetAccountBalance()) {

			cout << "\nYou Can't withdraw more than " << FromClient.GetAccountBalance() << ", Enter another amount: " << endl;
			return;
		}
		
		char sure = 'n';
		cout << "\nAre you sure you want to perform this transaction y/n ? ";
		cin >> sure;

		if (sure == 'Y' || sure == 'y') {

			FromClient.SetAccountBalance(FromClient.GetAccountBalance() - amount);
			ToClient.SetAccountBalance(ToClient.GetAccountBalance() + amount);
			
			FromClient.Save();
			ToClient.Save();

			cout << "\nTransfer Successfully.\n";
			_PrintMiniClientCard(FromClient);
			_PrintMiniClientCard(ToClient);
			_TransferLog(FromClient, ToClient, amount , "##");

		}

		else {

			cout << "\nOperation was cancelled.\n";
		}
	}
};

