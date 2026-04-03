#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>


class clsListUserScreen : protected clsScreen {

    static void _PrintUserRecordLine(clsUser user) {

        cout << setw(8) << left << "" << "| " << setw(12) << left << user.GetUsername();
        cout << "| " << setw(25) << left << user.GetFirstName() + " " + user.GetLastName();
        cout << "| " << setw(12) << left << user.GetPhone();
        cout << "| " << setw(20) << left << user.GetEmail();
        cout << "| " << setw(10) << left << user.GetPassword();
        cout << "| " << setw(12) << left << user.GetPermission();
    }

public:

	static void ShowUsersList() {

        vector <clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        
        else {

            for (clsUser u : vUsers) {

                _PrintUserRecordLine(u);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
	}
};

