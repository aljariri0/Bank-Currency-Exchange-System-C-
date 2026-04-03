#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

class clsAddNewClientScreen : protected clsScreen {


private:

    void static _ReadClientInfo(clsBankClient& client) {

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

    void static AddNewClient() {

        if (!CheckAccessRights(pow(2, 1))) {

            return;
        }

        clsScreen::_DrawScreenHeader("\tAdd New Client");


        cout << "\nEnter New Client Account Number : ";
        string account_number = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(account_number)) {

            cout << "\nAccount Is Already Exist, Please Enter another one: ";
            account_number = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::GetNewClientObject(account_number);
        _ReadClientInfo(client);

        clsBankClient::enSaveResults save_result = client.Save();

        switch (save_result) {

        case clsBankClient::enSaveResults::svSucceeded:

            cout << "\nClient Added Successfully :-)\n";
            client.Print();
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;

        case clsBankClient::enSaveResults::svFaildAccountNumberExists:

            cout << "\nError account was not saved because account number is used!\n";
            break;
        };
    }
};

