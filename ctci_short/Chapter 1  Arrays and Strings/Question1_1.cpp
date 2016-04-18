
/**
1.1 Implement an algorithm to determine if a string has all unique characters. What
if you cannot use additional data structures?
**/

#include<iostream>
#include<string>
using namespace std;

bool isUniqueChars(const string& str) {
    if (str.length() > 256) return false;

    unsigned int checker = 0;

    for (int i = 0; i < str.length(); ++i) {
        int value = str[i] - 'a';
        if ((checker & (1 << value)) != 0) return false;
        checker |= (1 << value);
    }

    return true;
}

bool isUniqueChars2(const string& str) {
    if (str.length() > 256) return false;

    bool ascii_set[256] = { false };

    for (int i = 0; i < str.length(); ++i) {
        int value = str[i];
        if (ascii_set[value]) return false;
        ascii_set[value] = true;
    }

    return true;
}


int main() {
    string input[] ={"abcde", "aba"};

    for (int i = 0; i < 2; i++) {
        cout << input[i] << " has unique characters: " << isUniqueChars(input[i]) << endl;
        cout << input[i] << " has unique characters: " << isUniqueChars2(input[i]) << endl;
    }

    return 0;
}
