#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen{

    static void _PrintUser(clsUser user) {

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

    static void ShowDeleteUserScreen() {

        _DrawScreenHeader("Delete User Screen");

        string username = "";

        cout << "\nEnter an Username: ";
        username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(username)) {

            cout << "\nThis username is not exist, choose another one: ";
            username = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::Find(username);
        _PrintUser(user);

        char answer = 'y';
        cout << "\nAre you sure you want to delete this user y/n ? ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            if (user.Delete()) {

                cout << "\nUser Deleted Successfully.\n";
                _PrintUser(user);
            }

            else
            {
                cout << "\nUser Wat not Deleted.\n";

            }
        }
    }
   
};

