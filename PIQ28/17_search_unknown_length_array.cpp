/**
    Search Unknown Length Array
    Given  a  sorted  array  of  unknown  length  and  a  number  to  search  for,  return  the  index  of  the
    number in the array. Accessing an element out of bounds throws exception. If the number occurs
    multiple times, return the index of any occurrence. If it isn’t present, return ­1.
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

int bin_search(vector<int> &v, int k) {
    int left = 0;
    int right = 1;

    while(v[right] < k && right < v.size() - 1) right *= 2;

    while(left < right) {
        int mid = (left + right)/2;
        if(v[mid] == k) return mid;
        else if(v[mid] < k) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

int main() {

    vector<int> v;
    for(int i = 0; i < 10; i++) v.push_back(i);

    cout << bin_search(v, 3) << endl;

    return 0;
}
