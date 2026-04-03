#pragma once
#include <iostream>
#include <vector>
#include "clsDate.h"


class clsUtil {

public:

	static void Srand() {

		srand(unsigned(time(NULL)));
	}

	static int RandomNumber(int from, int to) {

		return rand() % (to - from + 1) + from;
	}

	static enum enCharacterType {

		eLower = 0,
		eUpper = 1,
		eDigit = 3,
		eSpecialCharacter = 4,
		eMixCharacter = 5
	};

	static char GetRandomLowerCharacter() {

		return char(RandomNumber(97, 122));
	}

	static char GetRandomUpperCharacter() {

		return char(RandomNumber(65, 90));
	}

	static int GetRandomDigit() {

		return RandomNumber(0, 9);
	}

	static char GetRandomSpecialCharacter() {

		char sparry[] = { '$', '@', '#', '%', '&', '*', '!' };

		return sparry[RandomNumber(0, 6)];
	}

	static char GetRandomCharacter(enCharacterType r) {

		switch (r) {

		case enCharacterType::eLower:
			return GetRandomLowerCharacter();

		case enCharacterType::eUpper:
			return GetRandomUpperCharacter();

		case enCharacterType::eDigit:
			return GetRandomDigit() + '0';

		case enCharacterType::eSpecialCharacter:
			return GetRandomSpecialCharacter();

		case enCharacterType::eMixCharacter:
			return GetRandomCharacter((enCharacterType)RandomNumber(0, 4));
		}
	}

	static std::string GenerateRandomWord(enCharacterType r, int length) {

		std::string word = "";

		for (int i = 0; i < length; i++) {

			word += GetRandomCharacter(r);
		}

		return word;
	}

	static std::string GenerateRandomKey(enCharacterType r) {

		std::string word = "";

		for (int i = 1; i <= 16; i++) {

			word += GetRandomCharacter(r);

			if ((i == 4  || i == 8 || i == 12) && i != 16)
				word += '-';

		}

		return word;
	}

	static std::vector <std::string> GenerateRandomKeys(enCharacterType r, int number_of_keys) {

		std::vector <std::string> vKeys = {};

		for (int i = 0; i < number_of_keys; i++) {

			vKeys.push_back(GenerateRandomKey(r));
		}

		return vKeys;
	}


	static void Swap(int &a, int &b) {

		int temp = a;
		a = b;
		b = temp;
	}

	static void Swap(double &a, double &b) {

		double temp = a;
		a = b;
		b = temp;
	}

	static void Swap(std::string &a, std::string &b) {

		std::string temp = a;
		a = b;
		b = temp;
	}

	static void Swap(clsDate &a, clsDate &b) {

		clsDate temp = a;
		a = b;
		b = temp;
	}

	static void ShuffleArray(int arr[], int length) {

		for (int i = 0; i < length; i++) {

			Swap(arr[i], arr[RandomNumber(0, length - 1)]);
		}
	}

	static void ShuffleArray(std::string s[], int length) {

		for (int i = 0; i < length; i++) {

			Swap(s[i], s[RandomNumber(0, length - 1)]);
		}
	}


	static void FillArrayWithRandomNumbers(int arr[], int length, int from, int to) {

		for (size_t i = 0; i < length; i++) {

			arr[i] = RandomNumber(from, to);
		}
	}

	static void FillArrayWithRandomWords(string arr[], int length, enCharacterType r, int word_length) {

		for (size_t i = 0; i < length; i++) {

			arr[i] = GenerateRandomWord(r, word_length);
		}
	}


	static string Tabs(int tabs) {

		for (size_t i = 0; i < tabs; i++) {

			cout << "	";
		}
	}


	static std::string EncryptionText(std::string text, short encrypkey) {


		for (size_t i = 0; i < text.length(); i++) {

			text[i] += encrypkey;
		}

		return text;
	}

	static std::string DecryptionText(std::string text, short encrypkey) {


		for (size_t i = 0; i < text.length(); i++) {

			text[i] -= encrypkey;
		}

		return text;
	}
};

