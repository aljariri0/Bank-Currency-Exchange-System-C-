#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"


using namespace std;

class clsDeleteClientScreen : protected clsScreen
{


public:

    static void Delete() {

        clsScreen::_DrawScreenHeader("\tDelete Client");

        if (!CheckAccessRights(pow(2, 2))) {

            return;
        }

        cout << "\nEnter an Account Number : ";
        string account_number = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(account_number)) {

            cout << "\nAccount Is Not Exist, Please Enter another one: ";
            account_number = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(account_number);

        char c = 'n';
        cout << "\nAre you sure you want to delete this client y/n ? ";
        cin >> c;

        if (c == 'Y' || c == 'y') {

            if (client.Delete()) {

                cout << "\nClient Deleted Successfully.\n";
                client.Print();
            }

            else {

                cout << "\nError, Client Was Not Deleted\n";
            }
        }
    }
};

