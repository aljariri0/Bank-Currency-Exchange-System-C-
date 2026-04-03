#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class clsString
{
private:

    string _value;

public:

    clsString() { _value = ""; }

    clsString(string value) {

        this->_value = value;
    }

    string GetValue() {

        return _value;
    }

    static string ReadWords() {

        string words = "";

        cout << "Please Enter Your String? ";
        getline(cin, words);

        return words;
    }



    static void PrintFirstLetterEachWord(string words) {

        if (words[0] != ' ')
            cout << words[0] << "  ";

        for (int i = 0; i < words.length(); i++) {

            if (words[i] == ' ' && words[i + 1] != ' ') {
                cout << words[i + 1] << "  ";
            }
        }
    }

    void PrintFirstLetterEachWord() {

        PrintFirstLetterEachWord(_value);
    }


    static string UpperFirstLetterEachWord(string words) {

        bool is_first_letter = true;

        for (int i = 0; i < words.length(); i++) {

            if (words[i] != ' ' && is_first_letter) {

                words[i] = toupper(words[i]);
            }

            is_first_letter = (words[i] == ' ' ? true : false);
        }

        return words;
    }

    void UpperFirstLetterEachWord() {

        _value = UpperFirstLetterEachWord(_value);
    }



    static string UpperEachWord(string words) {

        for (int i = 0; i < words.length(); i++) {

            if (words[i] != ' ') {

                words[i] = toupper(words[i]);
            }
        }

        return words;
    }

    void UpperEachWord() {

        _value = UpperEachWord(_value);
    }



    static string LowerEachWord(string words) {

        for (int i = 0; i < words.length(); i++) {

            if (words[i] != ' ') {

                words[i] = tolower(words[i]);
            }
        }

        return words;
    }

    void LowerEachWord() {

        _value =  LowerEachWord(_value);
    }



    static void InvertCharahcter(char& c) {

        if (c >= 'a' && c <= 'z')
            c -= 32;

        else if (c >= 'A' && c <= 'Z')
            c += 32;
    }

    void InvertCharahcter(int i) {

        InvertCharahcter(_value[i]);
    }



    static void InvertAllCases(string& name) {

        for (int i = 0; i < name.length(); i++) {

            InvertCharahcter(name[i]);
        }
    }

    void InvertAllCases() {

        InvertAllCases(_value);
    }



    static void PhraseDetails(string phrase) {

        short upper = 0, lower = 0, length = 0;

        for (int i = 0; i < phrase.length(); i++) {

            if (isupper(phrase[i]))
                upper++;
            else if (islower(phrase[i]))
                lower++;

            if (phrase[i] != ' ' && !(ispunct(phrase[i])) && !(isdigit(phrase[i])))
                length++;
        }

        cout << "\n\nString length: " << length << endl;
        cout << "Capital letters: " << upper << endl;
        cout << "Lower letters: " << lower << endl;
    }

    void PhraseDetails() {

        PhraseDetails(_value);
    }


    static int CountSpecificLetter(string& sentence, char& letter, bool match_case = false) {

        short count_letter = 0;

        for (int i = 0; i < sentence.length(); i++) {


            if (match_case) {

                if (sentence[i] == letter)
                    count_letter++;
            }

            else {

                if (toupper(sentence[i]) == toupper(letter))
                    count_letter++;
            }
        }

        return count_letter;
    }

    int CountSpecificLetter(char letter, bool match_case = false) {

        return CountSpecificLetter(_value, letter, false);
    }


    static vector<string> Split(string sentence, string delimiter = " ") {

        size_t pos;
        vector<string> vWords;
        string word = "";

        while ((pos = sentence.find(delimiter)) != string::npos) {

            word = sentence.substr(0, pos);

            if (word != "")
                vWords.push_back(word);


            sentence.erase(0, pos + delimiter.length());
        }

        if(!sentence.empty())
            vWords.push_back(sentence);

        return vWords;
    }

    vector<string> Split() {

        return Split(_value);
    }



    static string RightTrim(string sentence) {

        if (sentence.empty())
            return "";

        for (size_t i = sentence.length(); i >= 0 ; i--)
        {
            if (sentence[i] != ' ') {

                return sentence.substr(0, i + 1);
            }
        }

        return sentence;
    }

    static string LeftTrim(string sentence) {

        if (sentence.empty())
            return "";

        for (int i = 0; i < sentence.length(); i++)
        {
            if (sentence[i] != ' ') {

                return sentence.substr(i, sentence.length());
            }
        }

        return sentence;
    }

    static string Trim(string sentence) {

        return RightTrim(LeftTrim(sentence));
    }


    string RightTrim() {

        return RightTrim(_value);
    }

    string LeftTrim() {

        return LeftTrim(_value);

    }

    string Trim() {

        return Trim(_value);
    }


    static string JoinString(vector <string>& vWords, string delimiter = " ") {

        string full_sentence = "";

        for (string& s : vWords) {

            full_sentence = full_sentence + s + delimiter;
        }

        return full_sentence.substr(0, full_sentence.length() - delimiter.length());
    }



    static string ReplaceSpecificWord(string sentence, string original_string, string replace_to) {

        size_t pos = sentence.find(original_string);

        while (pos != string::npos) {

            sentence = sentence.replace(pos, original_string.length(), replace_to);
            pos = sentence.find(original_string);
        }

        return sentence;
    }

    string ReplaceSpecificWord(string original_string, string replace_to) {

        return ReplaceSpecificWord(_value, original_string, replace_to);
    }

};

