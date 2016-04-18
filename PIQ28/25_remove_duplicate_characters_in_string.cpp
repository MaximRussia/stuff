/**
    Remove Duplicate Characters in String
    Remove duplicate characters in a given string keeping only the first occurrences. For example, if
    the input is ‘tree traversal’ the output will be ‘tre avsl’.
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

string remove_duplicates(string num) {
    string res;
    set<char> hash;
    for(char ch : num) {
        if(hash.find(ch) == hash.end()) {
            hash.insert(ch);
            res.push_back(ch);
        }
    }

    return res;
}

int main() {

    cout << remove_duplicates("Remove Duplicate Characters in String") << endl;

    return 0;
}
