#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Globel.h"

using namespace std;

class clsClientListScreen : public clsScreen {


private:

    void static _PrintClientRecordLine(clsBankClient& c) {

        cout << "| " << left << setw(15) << c.GetAccountNumber();
        cout << "| " << left << setw(25) << c.GetFirstName() + " " + c.GetLastName();
        cout << "| " << left << setw(15) << c.GetPhone();
        cout << "| " << left << setw(20) << c.GetEmail();
        cout << "| " << left << setw(15) << c.GetPinCode();
        cout << "| " << left << setw(15) << c.GetAccountBalance();
    }

    
public:

    void static ShowClientsList() {

        if (!CheckAccessRights(pow(2,0))) {

            return;
        }

        vector<clsBankClient> vClients = clsBankClient::GetClientList();

        clsScreen::_DrawScreenHeader("\tClients List");

        cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client's";
        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n\n";

        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(25) << "Client Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(15) << "PinCode ";
        cout << "| " << left << setw(15) << "Balance";

        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n\n";


        if (vClients.size() == 0)
            cout << "\n\t\t\t\tNo Clients are available !!.\n";

        else {

            for (clsBankClient& c : vClients) {

                _PrintClientRecordLine(c);
                cout << endl;
            }
        }

        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n\n";
    }
};

