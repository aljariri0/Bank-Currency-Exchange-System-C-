#pragma once
#include <iostream>
class clsPerson
{

private:

	std::string _first_name;
	std::string _last_name;
	std::string _email;
	std::string _phone;

public:

	clsPerson(std::string first_name, std::string last_name, std::string email, std::string phone) {

		_first_name = first_name;
		_last_name = last_name;
		_email = email;
		_phone = phone;
	}

	void SetFirstName(std::string first_name) {

		this->_first_name = first_name;
	}

	void SetLastName(std::string last_name) {

		this->_last_name = last_name;
	}

	void SetEmail(std::string email) {

		_email = email;
	}

	void SetPhone(std::string phone) {

		_phone = phone;
	}

	std::string GetFirstName() {

		return _first_name;
	}

	std::string GetLastName() {

		return _last_name;
	}

	std::string GetEmail() {

		return _email;
	}

	std::string GetPhone() {

		return _phone;
	}

};

