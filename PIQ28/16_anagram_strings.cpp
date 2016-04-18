/**
    16. Anagram Strings
    Given two strings, check if they’re anagrams or not. Two strings are anagrams if they are written
    using the same exact letters, ignoring space, punctuation and capitalization. Each letter should
    have the same count in both strings. For example, ‘Eleven plus two’ and ‘Twelve plus one’ are
    meaningful anagrams of each other.
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

bool is_anagrams(string str1, string str2) {

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    return str1 == str2;
}

int main() {

    cout << is_anagrams("abc", "cba") << endl;

    return 0;
}
