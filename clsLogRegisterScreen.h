#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Globel.h"
#include "clsUtil.h"
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

class clsLogRegisterScreen : protected clsScreen {

	struct stlog_register_info {

		string data_and_time;
		string username;
		string password;
		string permission;
	};

	static void _PrintTheHead() {

		cout << "\n__________________________________________";
		cout << "_____________________________________________\n\n";

		cout << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(15) << "Username";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(10)  << "Permission";

		cout << "\n__________________________________________";
		cout << "_____________________________________________\n\n";
	}

	static vector <string> _ConvertDataLineToVector(string data_line, string delimiter = "##") {

		vector <string> vLogs;

		string word = "";
		size_t pos;

		while ( (pos = data_line.find(delimiter) ) != string::npos) {

			word = data_line.substr(0, pos);

			if (word != "") {

				vLogs.push_back(word);
			}

			data_line.erase(0, pos + delimiter.length());
		}

		if (data_line != "")
			vLogs.push_back(data_line);

		return vLogs;
	}

	static stlog_register_info _ConvertToLogStructer(vector <string> vLogs) {

		stlog_register_info log;

		log.data_and_time = vLogs[0];
		log.username = vLogs[1];
		log.password = clsUtil::DecryptionText(vLogs[2], 11);
		log.permission = vLogs[3];

		return log;
	}

	static void _LoadAllLogRegisterFile(vector <stlog_register_info>& vLogs) {

		fstream file;
		file.open("LogRegister.txt", ios::in);

		vector <stlog_register_info> v_log_registers;

		if (file.is_open()) {

			string data_line = "";

			while (getline(file, data_line)) {

				vLogs.push_back(_ConvertToLogStructer(_ConvertDataLineToVector(data_line, "##")));
			}
		}

	}

	static void _PrintOneLogRegisterRecord(stlog_register_info& l) {

		cout << "| " << left << setw(25) << l.data_and_time;
		cout << "| " << left << setw(15) << l.username;
		cout << "| " << left << setw(15) << l.password;
		cout << "| " << left << setw(10) << l.permission;
	}

	static void _PrintLogRegisterFile(vector <stlog_register_info>& vLogs) {

		for (stlog_register_info l : vLogs) {

			_PrintOneLogRegisterRecord(l);
			cout << endl;
		}

		cout << endl;
	}

public:

	static void ShowRegisterScreen() {

		if (!CheckAccessRights(pow(2, 7))) {

			return;
		}

		vector <stlog_register_info> vLogs;
		_LoadAllLogRegisterFile(vLogs);

		clsScreen::_DrawScreenHeader("\t   Log Register", "   \t" +to_string(vLogs.size()) + " Record's");

		_PrintTheHead();

		_PrintLogRegisterFile(vLogs);

	}
};

