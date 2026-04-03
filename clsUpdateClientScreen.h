#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsUpdateClientScreen : protected clsScreen
{

    static void _ReadClientInfo(clsBankClient& client) {

        cout << "\nEnter FirstName: ";
        client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        client.SetAccountBalance(clsInputValidate::ReadDoubleNumber("Invalid number, try again: "));

    }

public:

    static void UpdateClient() {

        if (!CheckAccessRights(pow(2, 3))) {

            return;
        }

        clsScreen::_DrawScreenHeader("\tUpdate Client");


        cout << "\nEnter Client Account Number : ";
        string acccount_number = clsInputValidate::ReadString();

        clsBankClient client = clsBankClient::Find(acccount_number);


        if (!client.IsClientExist(acccount_number)) {

            cout << "\nAccount number is not found !!\n";

            system("pause>0");
            return;
        }

        cout << "\nUpdate Client Info's: \n";
        _ReadClientInfo(client);

        clsBankClient::enSaveResults save_result = client.Save();

        switch (save_result) {

        case clsBankClient::enSaveResults::svSucceeded:

            cout << "\nAccount Updated Successfully :-)\n";
            client.Print();
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }

    }

};

