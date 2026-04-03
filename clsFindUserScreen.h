#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen {


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

	static void ShowFindUserScreen() {

        _DrawScreenHeader("Find User Screen");

        string username = "";

        cout << "\nEnter an Username: ";
        username = clsInputValidate::ReadString();

        clsUser user = clsUser::Find(username);

        if (!user.IsEmpty()) {

            cout << "\nUser found\n";

        }
        else {

            cout << "\nUser Not found\n";

        }

        _PrintUser(user);
	}
};

