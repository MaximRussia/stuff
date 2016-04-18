
/**
    Combine Two Strings
    We are given 3 strings: str1, str2, and str3. Str3 is said to be a shuffle of str1 and str2 if it can be
    formed by interleaving the characters of str1 and str2 in a way that maintains the left to right
    ordering  of  the  characters  from  each  string.  For  example,  given  str1=”abc”  and  str2=”def”,
    str3=”dabecf” is a valid shuffle since it preserves the character ordering of the two strings. So,
    given these 3 strings write a function that detects whether str3 is a valid shuffle of str1 and str2.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

bool isPermutation1(const string &s1, const string &s2, const string &s3) {
    if(s1.size() + s2.size() != s3.size())
        return false;

    if(s1 + s2 == s3)
        return true;

    if(s1[0] != s3[0] && s2[0] != s3[0])
        return false;

    if(s1[0] == s3[0] && isPermutation1(s1.substr(1, s1.size()-1), s2, s3.substr(1, s3.size()-1)))
        return true;

     if(s2[0] == s3[0] && isPermutation1(s1, s2.substr(1, s2.size()-1), s3.substr(1, s3.size()-1)))
        return true;

    return false;
}

bool permut(string s1, string s2, int l, int r) {
    if( l > r) {
        return s1 == s2;
    }

    for(int i = l; i <= r; i++) {
        swap(s1[i], s1[l]);
        if(permut(s1, s2, l+1, r)) {
            return true;
        }
        swap(s1[i], s1[l]);
    }

    return false;
}

bool isPermutImpl(string s1, string s2, string s3) {
    string s = s1 + s2;
    return permut(s, s3, 0, s.size()-1);
}


int main() {

    cout << isPermutImpl("abc", "cdf", "cdfabc") << endl;
    cout << isPermutImpl("abv", "cdf", "cdfabc") << endl;

    return 0;
}
