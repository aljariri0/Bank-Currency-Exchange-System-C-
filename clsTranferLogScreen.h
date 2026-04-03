#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Globel.h"
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

class clsTranferLogScreen : protected clsScreen {

	struct stlog_register_info {

		string data_and_time;
		string source_account_number;
		string destenation_account_number;
		double amount = 0;
		double source_balance;
		double destenation_balance;
		string username;
	};

	static void _PrintTheHead() {

		cout << "\n_________________________________________________________";
		cout << "___________________________________________________________\n\n";

		cout << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(20) << "s.Account Number";
		cout << "| " << left << setw(20) << "d.Account Number";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(10) << "User";

		cout << "\n_________________________________________________________";
		cout << "___________________________________________________________\n\n";
	}

	static void _PrintOneTransferLogRecord(stlog_register_info& l) {

		cout << "| " << left << setw(25) << l.data_and_time;
		cout << "| " << left << setw(20) << l.source_account_number;
		cout << "| " << left << setw(20) << l.destenation_account_number;
		cout << "| " << left << setw(10) << l.amount;
		cout << "| " << left << setw(10) << l.source_balance;
		cout << "| " << left << setw(10) << l.destenation_balance;
		cout << "| " << left << setw(10) << l.username;
	}

	static void _PrintTransferLogFile(vector <stlog_register_info>& vLogs) {

		for (stlog_register_info& l : vLogs) {

			_PrintOneTransferLogRecord(l);
			cout << endl;
		}

		cout << endl;
	}

	static vector <string> _ConvertDataLineToVector(string data_line, string delimiter = "##") {

		vector <string> vTLogs;

		string word = "";
		size_t pos;

		while ((pos = data_line.find(delimiter)) != string::npos) {

			word = data_line.substr(0, pos);

			if (word != "") {

				vTLogs.push_back(word);
			}

			data_line.erase(0, pos + delimiter.length());
		}

		if (data_line != "")
			vTLogs.push_back(data_line);

		return vTLogs;
	}

	static stlog_register_info _ConvertToLogStructer(vector <string> vTLogs) {

		stlog_register_info log;

		log.data_and_time = vTLogs[0];
		log.source_account_number = vTLogs[1];
		log.destenation_account_number = vTLogs[2];
		log.amount = stod(vTLogs[3]);
		log.source_balance = stod(vTLogs[4]);
		log.destenation_balance = stod(vTLogs[5]);
		log.username = vTLogs[6];

		return log;
	}


	static void _LoadAllTransferLogFile(vector <stlog_register_info>& vTLogs) {

		fstream file;
		file.open("TrasferLog.txt", ios::in);

		vector <stlog_register_info> v_log_registers;

		if (file.is_open()) {

			string data_line = "";

			while (getline(file, data_line)) {

				vTLogs.push_back(_ConvertToLogStructer(_ConvertDataLineToVector(data_line, "##")));
			}
		}

	}

public:

	static void ShowTranferLogScreen() {

		vector <stlog_register_info> vTLogs;
		_LoadAllTransferLogFile(vTLogs);

		clsScreen::_DrawScreenHeader("\t   Transfer Log", "   \t" + to_string(vTLogs.size()) + " Record's");

		_PrintTheHead();
		_PrintTransferLogFile(vTLogs);
	}
};

