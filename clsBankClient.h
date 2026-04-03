#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsPerson.h"

using namespace std;

class clsBankClient : public clsPerson {

private:

	enum enMode { 

		eEmptyMode = 0,
		eUpdateMode = 1,
		eAddNewMode = 2
	};

	string _account_number;
	string _pin_code;
	float _account_balance;
	enMode _mode;
	bool _mark_for_delete = false;

	static clsBankClient _ConvertStringVectorToBankClientObject(vector<string> vClients) {

		return clsBankClient(enMode::eUpdateMode, vClients[0], vClients[1], vClients[2], vClients[3], vClients[4], vClients[5], stof(vClients[6]));
	}

	static clsBankClient _GetEmptyBankClientObject() {

		return clsBankClient(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadAllClientsDataFromFile() {

		fstream file;
		vector<clsBankClient> vClients;

		file.open("Clients.txt", ios::in);

		if (file.is_open()) {

			string data_line;

			while (getline(file, data_line)) {

				vClients.push_back(_ConvertStringVectorToBankClientObject(clsString::Split(data_line, ",")));
			}

			file.close();
		}

		return vClients;
	}

	static string _ClientBankObjectToDataLine(clsBankClient& c, string delimiter = ",") {

		string data_line = c.GetFirstName() + delimiter + c.GetLastName() + delimiter +
			c.GetEmail() + delimiter + c.GetPhone() + delimiter + c.GetAccountNumber() +
			delimiter + c.GetPinCode() + delimiter + to_string(c.GetAccountBalance());
 

		return data_line;
	}

	static void _SaveAllClientsInfoToFile(vector<clsBankClient>& vClients) {

		fstream file;

		file.open("Clients.txt", ios::out);

		if (file.is_open()) {

			for (clsBankClient& c : vClients) {

				if(c._mark_for_delete == false)
					file << _ClientBankObjectToDataLine(c) << endl;
			}

			file.close();
		}
	}

	void _AddDataLineToFile(string data_line) {

		fstream file;

		file.open("Clients.txt", ios::out | ios::app);

		if (file.is_open()) {

			file << data_line << endl;

			file.close();
		}
	}

	void _Update() {

		vector<clsBankClient> vClients = _LoadAllClientsDataFromFile();

		for (clsBankClient &c : vClients) {

			if (c.GetAccountNumber() == this->GetAccountNumber()) {

				c = *this;
				break;
			}
		}

		_SaveAllClientsInfoToFile(vClients);
	}

	void _AddNew() {

		_AddDataLineToFile(_ClientBankObjectToDataLine(*this));
	}

public:

	clsBankClient(enMode mode, string first_name, string last_name, string email, string phone, string account_number, string pin_code, float account_balance)
		: clsPerson(first_name, last_name, email, phone) {

		_mode = mode;
		_account_number = account_number;
		_pin_code = pin_code;
		_account_balance = account_balance;
	}

	static enum enSaveResults {

		svFaildEmptyObject = 0,
		svSucceeded = 1,
		svFaildAccountNumberExists = 2
	};

	bool IsEmpty() {

		return (_mode == enMode::eEmptyMode);
	}

	string GetAccountNumber() {

		return _account_number;
	}

	string GetPinCode() {

		return _pin_code;
	}

	float GetAccountBalance() {

		return _account_balance;
	}

	void SetPinCode(string pin_code) {

		_pin_code = pin_code;
	}

	void SetAccountBalance(float balance) {

		_account_balance = balance;
	}

	void Print() {

		cout << "\nClient Card: ";
		cout << "\n_____________";
		cout << "\nFirst Name : " << GetFirstName();
		cout << "\nLast Name  : " << GetLastName();
		cout << "\nFull Name  : " << GetFirstName() + " " + GetLastName();
		cout << "\nEmail      : " << GetEmail();
		cout << "\nPhone      : " << GetPhone();
		cout << "\nBalance    : " << GetAccountBalance();
		cout << "\nPassword   : " << GetPinCode();
		cout << "\n------------\n";
	}

	static clsBankClient Find(string account_number) {

		vector<clsBankClient> vClients;

		fstream file;

		file.open("Clients.txt", ios::in);

		if (file.is_open()) {

			string data_line = "";

			while (getline(file, data_line)) {

				clsBankClient client = _ConvertStringVectorToBankClientObject(clsString::Split(data_line, ","));

				if (client.GetAccountNumber() == account_number) {

					file.close();
					return client;
				}

				vClients.push_back(client);
			}

			file.close();
		}

		return _GetEmptyBankClientObject();
	}

	static clsBankClient Find(string account_number, string pin_code) {

		vector<clsBankClient> vClients;

		fstream file;

		file.open("Clients.txt", ios::in);

		if (file.is_open()) {

			string data_line = "";

			while (getline(file, data_line)) {

				clsBankClient client = _ConvertStringVectorToBankClientObject(clsString::Split(data_line, ","));

				if (client.GetAccountNumber() == account_number && client.GetPinCode() == pin_code) {

					file.close();
					return client;
				}

				vClients.push_back(client);
			}

			file.close();
		}

		return _GetEmptyBankClientObject();
	}

	static bool IsClientExist(string account_number) {

		clsBankClient client = clsBankClient::Find(account_number);

		return (!client.IsEmpty());
	}

	enSaveResults Save() {

		switch (_mode) {

		case enMode::eEmptyMode:
			return enSaveResults::svFaildEmptyObject;


		case enMode::eUpdateMode:

			_Update();

			return enSaveResults::svSucceeded;

		case enMode::eAddNewMode:

			if (IsClientExist(_account_number))
				return enSaveResults::svFaildAccountNumberExists;
			
			else {

				_AddNew();
				_mode = enMode::eUpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient GetNewClientObject(string account_number) {

		return clsBankClient(enMode::eAddNewMode, "", "", "", "", account_number, "", 0);
	}

	bool Delete() {

		bool found = false;

		vector<clsBankClient> vClient = _LoadAllClientsDataFromFile();

		for (clsBankClient& c : vClient) {

			if (c.GetAccountNumber() == this->GetAccountNumber()) {

				c._mark_for_delete = true;
				found = true;
				break;
			}
		}

		_SaveAllClientsInfoToFile(vClient);

		*this = _GetEmptyBankClientObject();

		return found;
	}

	static vector<clsBankClient> GetClientList() {

		return _LoadAllClientsDataFromFile();
	}
};

