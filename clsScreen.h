#pragma once
#include <iostream>
#include "Globel.h"
#include "clsDate.h"
using namespace std;


class clsScreen
{

protected:

    static void _DrawScreenHeader(string title, string sub_title = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;

        if (sub_title != "") {

            cout << "\n\t\t\t\t\t  " << sub_title;
        }

        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\n\t\t\t\t\t";

        clsDate date = clsDate::GetSystemDate();

        cout << "User: " << GlobelUser::CurrentUser.GetUsername() << "\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate());


        cout << "\n\t\t\t\t\t______________________________________\n\n";
    }

    static bool CheckAccessRights(int p) {

        if (!GlobelUser::CurrentUser.CheckPermission(p)) {

            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }

        return true;
    }
};

