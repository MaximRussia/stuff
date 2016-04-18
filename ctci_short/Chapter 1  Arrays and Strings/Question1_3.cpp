
/**
1.3 Given two strings, write a method to decide if one is a permutation of the other.
**/

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

bool permutation_1(string a, string b) {
    if(a.size() != b.size()) return false;
    if(a.empty() || b.empty()) return false;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    return a == b;
}

bool permutation_2(string a, string b) {
    if(a.size() != b.size()) return false;

    int ascii_set[256] = {0};

    for (int i = 0; i < a.length(); i++)
        ascii_set[a[i]]++;

    for (int i = 0; i < b.length(); i++) {
        --ascii_set[b[i]];

        if(ascii_set[b[i]] < 0) return false;
    }

    return true;
}

int main() {
    string a = "apple";
    string b = "papel";

    cout << "Result for " << a << " and " << b << " is " << permutation_1(a, b) << endl;
    cout << "Result for " << a << " and " << b << " is " << permutation_2(a, b) << endl;

    return 0;
}
