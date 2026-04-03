#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen {

public:

    static void ShowFindClientScreen() {

        if (!CheckAccessRights(pow(2, 4))) {

            return;
        }

        clsScreen::_DrawScreenHeader("\tFind Client");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);

        if (!client.IsEmpty()) {

            client.Print();
        }

        else {

            cout << "\nClient Was not Found :-(\n";
        }

    }
};

