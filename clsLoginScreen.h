#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Globel.h"
#include "clsDate.h"
#include <fstream>

using namespace std;

class clsLoginScreen :protected clsScreen { 


private:

	static void LogRegisterFile(clsUser& user_log, string delimiter = "##") {

		fstream file;

		file.open("LogRegister.txt", ios::out | ios::app);

		if (file.is_open()) {

			file << clsDate::DateToString(clsDate::GetSystemDate()) << " - " << clsDate::GetSystemTime() << delimiter
				<< user_log.GetUsername() << delimiter << clsUtil::EncryptionText(user_log.GetPassword(), 11) << delimiter << user_log.GetPermission() << endl;

			file.close();
		}
	}

	static void _Login(short& trials) {

		bool login_falid = false;
		string username, password;

		do
		{
			if (login_falid) {

				cout << "\nInvalid Username/Password!";
				cout << "\nYou have " << trials << " Trials to login.\n";
				trials--;
			}
				

			cout << "\nEnter Username: ";
			cin >> username;

			cout << "\nEnter Password: ";
			cin >> password;

			GlobelUser::CurrentUser = clsUser::Find(username, password);
			login_falid = GlobelUser::CurrentUser.IsEmpty();

		} while (login_falid && trials != 0);


		if (trials != 0) {

			LogRegisterFile(GlobelUser::CurrentUser);
			clsMainScreen::ShowMainMenue();
		}
			

		else {
			
			cout << "\nYou have locked after 3 faild trials.\n";
			return;
		}
	}

public:

	static void ShowLoginScreen(short& trials) {

		system("cls");
		clsScreen::_DrawScreenHeader("\t    Login Screen");
		_Login(trials);
	}
};

