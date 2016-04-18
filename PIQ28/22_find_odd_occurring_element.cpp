/**
    Find Odd Occurring Element
    Given  an  integer  array,  one  element  occurs  odd  number  of  times  and  all  others  have  even
    occurrences. Find the element with odd occurrences.
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

int find_odd(vector<int> odd) {

    int result = 0;

    for(int i = 0; i < odd.size(); i++) {
        result ^= odd[i];
    }

    return result;
}

int main() {

    vector<int> odd = {1, 2, 3, 1, 2, 3, 1};

    cout << find_odd(odd) << endl;

    return 0;
}
