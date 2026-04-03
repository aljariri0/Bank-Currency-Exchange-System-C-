#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsScreen.h"

using namespace std;


class clsManageUsersScreen : protected clsScreen{

private:

    enum enManageUsers {

        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenu = 6
    };

    static void _GoBackToManageUsersScreen() {

        cout << setw(37) << left << "" << "\nPress any key to go back to Manage Users Menue...\n";
        system("pause>0");

        ShowManageUsersScreen();
    }

    static int _ReadManageUsersMenueOption(int a, int b) {

        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1 to 6]? ";

        int number = clsInputValidate::ReadIntNumber("Invalid Option, Enter again between [1 to 6]: ");

        return number;
    }

    static void _ShowListUserScreen() {

        clsListUserScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen() {

        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen() {

        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {

        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {

        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersOptions(enManageUsers o) {

        switch (o) {

        case enManageUsers::eListUsers:

            system("cls");

            _ShowListUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsers::eAddNewUser:

            system("cls");

            _ShowAddNewUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsers::eDeleteUser:

            system("cls");

            _ShowDeleteUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsers::eUpdateUser:

            system("cls");

            _ShowUpdateUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsers::eFindUser:

            system("cls");

            _ShowFindUserScreen();
            _GoBackToManageUsersScreen();
            break;

        case enManageUsers::eMainMenu:

            system("cls");
            break;
        }
    }


public:

	static void ShowManageUsersScreen() {

        if (!CheckAccessRights(pow(2, 6))) {

            return;
        }

        system("cls");

        clsScreen::_DrawScreenHeader("\tManage Users");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersOptions((enManageUsers)_ReadManageUsersMenueOption(1, 6));
	}
};

