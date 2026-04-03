#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class clsUser : public clsPerson {

private:

	enum enMode {

		eEmptyMode = 0,
		eUpdateMode = 1,
		eAddNewMode = 2
	};

	enMode _mode;
	string _username;
	string _password;
	int _permission;
	bool mark_for_delete = false;


	static vector<string> _SplitUserObject(string data_line, string delimiter = ",") {

		size_t pos;
		string word = "";
		vector <string> vUser;

		while (  (pos = data_line.find(delimiter)) != string::npos  ) {

			word = data_line.substr(0, pos);

			if (word != "")
				vUser.push_back(word);

			data_line.erase(0, pos + delimiter.length());
		}

		if (!data_line.empty())
			vUser.push_back(data_line);


		return vUser;
	}

	static clsUser _ConvertDataLineToUserObject(string data_line, string delimiter = ",") {

		vector<string> vUsers = _SplitUserObject(data_line, delimiter);

		return clsUser(enMode::eUpdateMode,vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4], clsUtil::DecryptionText(vUsers[5], 11), stoi(vUsers[6]));
	}

	static vector <clsUser> _LoadAllUsersFromFile() {

		vector <clsUser> vUsers;

		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open()) {

			string data_line = "";

			while (getline(file, data_line)) {

				if (data_line.empty())
					continue;

				vUsers.push_back(_ConvertDataLineToUserObject(data_line, ","));
			}

			file.close();
		}

		return vUsers;
	}

	static string _ConvertUserObjectToDataLine(clsUser& u, string delimiter = ",") {

		string data_line = u.GetFirstName() + delimiter + u.GetLastName() + delimiter +
			u.GetEmail() + delimiter + u.GetPhone() + delimiter + u.GetUsername() +
			delimiter + clsUtil::EncryptionText(u.GetPassword(), 11) + delimiter + to_string(u.GetPermission());


		return data_line;
	}

	static void _SaveAllUsersInfoToFile(vector <clsUser>& vUsers) {

		fstream file;
		file.open("Users.txt", ios::out);


		if (file.is_open()) {

			for (clsUser& u : vUsers) {

				if(u.mark_for_delete == false)
					file << _ConvertUserObjectToDataLine(u, ",") << endl;
			}

			file.close();
		}
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update() {

		vector <clsUser> vUsers = _LoadAllUsersFromFile();

		for (clsUser& u : vUsers) {

			if (u.GetUsername() == _username) {

				u = *this;
				break;
			}
		}

		_SaveAllUsersInfoToFile(vUsers);
	}

	void _AddNew() {

		fstream file;
		file.open("Users.txt", ios::out | ios::app);

		if (file.is_open()) {

			string data_line = _ConvertUserObjectToDataLine(*this);

			file << data_line << endl;

			file.close();
		}
	}

public:

	clsUser(enMode mode, string first_name, string last_name, string email, string phone, string username, string password, int permission) 
		: clsPerson(first_name, last_name, email, phone) {

		_mode = mode;
		_username = username;
		_password = password;
		_permission = permission;
	}

	static bool IsUserExist(string username) {

		clsUser user = clsUser::Find(username);

		return (!user.IsEmpty());
	}

	bool IsEmpty() {

		return _mode == enMode::eEmptyMode;
	}

	string GetUsername() {

		return _username;
	}

	void SetUsername(string username) {

		_username = username;
	}

	string GetPassword() {

		return _password;
	}

	void SetPassword(string password) {

		_password = password;
	}

	void SetPermission(int permission) {

		_permission = permission;
	}

	int GetPermission() {

		return _permission;
	}

	static clsUser Find(string username) {

		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open()) {

			string data_line;

			while (getline(file, data_line)) {

				clsUser user = _ConvertDataLineToUserObject(data_line, ",");

				if (user.GetUsername() == username) {

					file.close();
					return user;
				}
			}

			file.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string username, string password) {

		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open()) {

			string data_line;

			while (getline(file, data_line)) {

				clsUser user = _ConvertDataLineToUserObject(data_line, ",");

				if (user.GetUsername() == username && user.GetPassword() == password) {

					file.close();
					return user;
				}
			}

			file.close();
		}

		return _GetEmptyUserObject();
	}

	bool Delete() {

		bool found = false;
		vector <clsUser> vUsers = _LoadAllUsersFromFile();

		for (clsUser& u : vUsers) {

			if (u._username == _username) {

				u.mark_for_delete = true;
				found = true;
				break;
			}
		}

		_SaveAllUsersInfoToFile(vUsers);
		*this = _GetEmptyUserObject();

		return found;
	}

	static enum enSaveResults {

		svFaildEmptyObject = 0,
		svSucceeded = 1,
		svFaildUserExist = 2
	};

	enSaveResults Save() {
		
		switch (_mode) {

		case enMode::eEmptyMode:

			if(IsEmpty())
				return enSaveResults::svFaildEmptyObject;

			break;

		case enMode::eUpdateMode:

			_Update();

			return enSaveResults::svSucceeded;

			break;

		case enMode::eAddNewMode:

			if (IsUserExist(_username)) {

				return enSaveResults::svFaildUserExist;
			}

			_AddNew();

			_mode = enMode::eUpdateMode;
			return enSaveResults::svSucceeded;

			break;
		}
	}

	static clsUser GetAddNewUserObject(string username) {

		return clsUser(enMode::eAddNewMode, "", "", "", "", username, "", 0);
	}

	static vector <clsUser> GetUsersList() {

		return _LoadAllUsersFromFile();
	}

	bool CheckPermission(int p) {

		if (p == -1)
			return true;

		else if ( (p & _permission) == p)
			return true;

		return false;
	}
};

