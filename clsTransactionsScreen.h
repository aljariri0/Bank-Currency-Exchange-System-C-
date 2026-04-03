#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepsitScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTranferLogScreen.h"

using namespace std;


class clsTransactionsScreen : protected clsScreen {


private:

    static enum enTransactions {

        eDeposit = 1,
        eWithdraw = 2,
        eTotalBalance = 3,
        eTransfer = 4,
        eTransferLog = 5,
        eMainMenue = 6
    };

    static void _ShowDepoistScreen() {

        clsDepsitScreen::ShowDepositScreen();
    }

    static void _ShowWithDrawScreen() {

        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalanceScreen() {

        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _GoBackToTransactionScreen() {

        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");

        ShowTransactionsMenue();
    }

    static int _ReadTransactionMenueOption(int a, int b) {

        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1 to 6]? ";

        int number = clsInputValidate::ReadIntNumber("Invalid Option, Enter again between 1 to 6: ");

        return number;
    }

    static void _ShowTransferScreen() {

        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {

        clsTranferLogScreen::ShowTranferLogScreen();
    }

    static void _PerformTransactionsMenue(enTransactions o) {

        switch (o) {

        case enTransactions::eDeposit:
            
            system("cls");
            _ShowDepoistScreen();
            _GoBackToTransactionScreen();

            break;

        case enTransactions::eWithdraw:

            system("cls");
            _ShowWithDrawScreen();
            _GoBackToTransactionScreen();

            break;

        case enTransactions::eTotalBalance:

            system("cls");
            _ShowTotalBalanceScreen();
            _GoBackToTransactionScreen();

            break;

        case enTransactions::eTransfer:

            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionScreen();

            break;

        case enTransactions::eTransferLog:

            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionScreen();

            break;

        case enTransactions::eMainMenue:

            system("cls");
            //clsMainScreen::ShowMainMenue();

            break;
        }
    }


public:

	static void ShowTransactionsMenue() {

        if (!CheckAccessRights(pow(2, 5))) {

            return;
        }

        system("cls");
        clsScreen::_DrawScreenHeader("\tTransactions");


        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenue((enTransactions)_ReadTransactionMenueOption(1,6));
	}
};

