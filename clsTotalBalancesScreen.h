#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsMainScreen.h"

using namespace std;


class clsTotalBalancesScreen {

    static void PrintClientRecordLineForTotalBalances(clsBankClient& c) {

        cout << "| " << left << setw(15) << c.GetAccountNumber();
        cout << "| " << left << setw(25) << c.GetFirstName() + " " + c.GetLastName();
        cout << "| " << left << setw(15) << c.GetAccountBalance();
    }

public:

    static void ShowTotalBalances() {

        vector<clsBankClient> vClients = clsBankClient::GetClientList();

        cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client's";
        cout << "\n________________________________________";
        cout << "__________________________________________\n\n";

        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(25) << "Client Name";
        cout << "| " << left << setw(20) << "Balance";

        cout << "\n________________________________________";
        cout << "__________________________________________\n\n";

        double total = 0;

        if (vClients.size() == 0)
            cout << "\n\t\t\t\tNo Clients are available !!.\n";


        else {

            for (clsBankClient& c : vClients) {

                total += c.GetAccountBalance();

                PrintClientRecordLineForTotalBalances(c);
                cout << endl;
            }
        }

        cout << "\n________________________________________";
        cout << "__________________________________________\n\n";

        cout << "\t\t\t\tTotal Balances = " << total << endl;

    }

};

