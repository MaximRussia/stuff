/**
    Find Next Palindrome Number
    Given a number, find the next smallest palindrome larger than the number. For example if the
    number is 125, next smallest palindrome is 131.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cstring>
using namespace std;

string reverse(string str) {
    reverse(str.begin(), str.end());
    return str;
}

string to_str(int i) {
    string res = "";
    int buf = 0;
    while(buf = i % 10) {
        res = string(1, '0' + buf) + res;
        i /= 10;
    }
    return res;
}

int to_int(string str) {
    return atoi(str.c_str());
}

string roundUp(string str) {
    int v = to_int(str);
    int increment = pow(10, str.size()/2+1);
    int next = (v/increment + 1)*increment;
    return to_str(next);
}

string next_palindrom_number(string str) {

    bool evenDigits = str.size()%2 == 0;
    string left = str.substr(0, str.size()/2);
    string revert = reverse(left);
    string res = "";

    if(evenDigits) res = left + revert;
    else {
        string middle = string(1, str[(str.size()-1)/2]);
        res = left + middle + revert;
    }

    if(to_int(res) > to_int(str))
        return res;

    return next_palindrom_number(roundUp(str));
}

int main() {

    cout << next_palindrom_number("123") << endl;
    return 0;
}
