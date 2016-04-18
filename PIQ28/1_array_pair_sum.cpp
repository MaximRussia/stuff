
/**
    Given an integer array, output all pairs that sum up to a specific value k.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

/// sort + bin search
vector<pair<int, int>> pairSum1(vector<int> arr, int k) {
    vector<pair<int, int>> res;
    if(arr.size() < 2) return res;

    sort(arr.begin(), arr.end());
    int left = 0, right = arr.size()-1;

    while(left < right) {
        int currSumm = arr[left] + arr[right];
        if(currSumm == k) {
            res.push_back(pair<int, int>(arr[left], arr[right]));
            left++;
        } else if (currSumm < k) left++;
        else right--;
    }

    return res;
}

/// hash
vector<pair<int, int>> pairSum2(vector<int> arr, int k) {
    vector<pair<int, int>> res;
    if(arr.size() < 2) return res;
    map<int, int> hash;

    for(int i = 0; i < arr.size(); i++) {
        int diff = k - arr[i];
        hash[arr[i]] = i;
        if(hash.find(diff) != hash.end()) {
            res.push_back(pair<int, int>(hash[diff], i));
        }
    }

    return res;
}

int main() {

    vector<int> v;
    for(int i = 0; i < 10; i++) v.push_back(i);

    vector<pair<int, int>> res = pairSum2(v, 5);

    for(int i = 0; i < res.size(); i++) {
        cout << res[i].first << " " << res[i].second << endl;
     }
}
