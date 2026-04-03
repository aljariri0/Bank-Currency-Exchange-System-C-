#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "clsLogRegisterScreen.h"
#include "clsCurrencyScreen.h"
#include "Globel.h"


using namespace std;

class clsMainScreen : protected clsScreen {

private:

    enum enMainMenueScreen {

        eShowClient = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eTransactions = 6,
        eManageUsers = 7,
        eLogRegister = 8,
        eCurrency = 9,
        eLogout = 10
    };

    static int _ReadMainMenueOption(int a, int b) {

        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1 to 10]? ";

        int number = clsInputValidate::ReadIntNumber("Invalid Option, Enter again between 1 to 10: ");

        return number;
    }

    static void _ShowAllClientsScreen() {

        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen() {

        clsAddNewClientScreen::AddNewClient();
    }

    static void _ShowDeleteClientScreen() {

        clsDeleteClientScreen::Delete();
    }

    static void _ShowUpdateClientScreen() {
        
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen() {

        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue() {

        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue() {

        clsManageUsersScreen::ShowManageUsersScreen();
    }
    
    static void _ShowLogRegisterScreen() {

        clsLogRegisterScreen::ShowRegisterScreen();
    }

    static void _Logout() {

        GlobelUser::CurrentUser = clsUser::Find("", "");
    }

    static void _ShowCurrencyExchangeScreen() {

        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");

        ShowMainMenue();
    }


    static void _PerformMainMenueOptions(enMainMenueScreen o) {

        switch (o) {

        case enMainMenueScreen::eShowClient:

            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eAddNewClient:

            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eDeleteClient:

            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eUpdateClient:

            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eFindClient:

            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eTransactions:

            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eManageUsers:

            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eLogRegister:

            system("cls");
            _ShowLogRegisterScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eCurrency:

            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueScreen::eLogout:

            system("cls");
            _Logout();

            break;
        }
    }

public:

	static void ShowMainMenue() {

        system("cls");
        clsScreen::_DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Log Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenueOptions((enMainMenueScreen)_ReadMainMenueOption(1, 10));
	}
};

