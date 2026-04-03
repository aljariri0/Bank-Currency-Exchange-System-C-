#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;


class clsAddNewUserScreen : protected clsScreen {

    static int _ReadPermissions() {

        int permission = 0;
        char answer = 'n';

        cout << "\nDo you want give full permission y/n?  ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission = -1;
            return permission;
        }

        cout << "\nDo you want to give access to : \n";

        cout << "\nShow Client List? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission += pow(2, 0);
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            permission += pow(2, 1);
        }

        cout << "\nDelete Client? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            permission += pow(2, 2);
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission += pow(2, 3);
        }

        cout << "\nFind Client? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission += pow(2, 4);
        }

        cout << "\nTransactions? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission += pow(2, 5);
        }

        cout << "\nManage Users? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission += pow(2, 6);
        }

        cout << "\nLogin Register? y/n? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            permission += pow(2, 7);
        }

        return permission;
    }

    static void _ReadUserInfo(clsUser& user) {

        cout << "\nEnter FirstName: ";
        user.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        user.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        user.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        user.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        user.SetPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permission: ";
        user.SetPermission(_ReadPermissions());

    }

    static void _PrintUser(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.GetFirstName();
        cout << "\nLastName    : " << user.GetLastName();
        cout << "\nFull Name   : " << user.GetFirstName() + " " + user.GetLastName();
        cout << "\nEmail       : " << user.GetEmail();
        cout << "\nPhone       : " << user.GetPhone();
        cout << "\nUser Name   : " << user.GetUsername();
        cout << "\nPassword    : " << user.GetPassword();
        cout << "\nPermissions : " << user.GetPermission();
        cout << "\n___________________\n";

    }

public:

	static void ShowAddNewUserScreen() {

		_DrawScreenHeader("Add New User");

        string username = "";

        cout << "\nEnter an Username: ";
        username = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(username)) {

            cout << "\nThis username is already exist, choose another one: ";
            username = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::GetAddNewUserObject(username);

        _ReadUserInfo(user);

        clsUser::enSaveResults save_result = user.Save();

        switch (save_result) {

        case clsUser::enSaveResults::svSucceeded:

            cout << "\nUser Saved Successfully.\n";
            _PrintUser(user);

            break;

        case clsUser::enSaveResults::svFaildUserExist:

            cout << "\nError, This user is empty.\n";

            break;

        case clsUser::enSaveResults::svFaildEmptyObject:

            cout << "\nError, This user is alreay Exist.\n";
            break;

        }
	}
};

