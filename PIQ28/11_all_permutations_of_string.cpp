/**
    All Permutations of String
    Generate all permutations of a given string.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

/// O(n!)
vector<string> string_permutation_1(string str) {
    vector<string> res;
    if(str.empty()) {
        return vector<string>();
    }
    if(str.size() == 1) {
        res.push_back(str);
        return res;
    }

    string substring = str.substr(1, str.size()-1);
    vector<string> strings = string_permutation_1(substring);

    for(auto s : strings) {
        /// add char in the middle
        for(int i = 0; i < s.size(); ++i) {
            string insert_str = s;
            insert_str.insert(i, 1, str[0]);
            res.push_back(insert_str);
        }
        /// add char in the end
        res.push_back(s+str[0]);
    }
    return res;
}

int main() {

    vector<string> res = string_permutation_1("qwe");
    cout << res.size() << endl;

    for(auto str : res) {
        cout << "main : " << str << endl;
    }

    return 0;
}
