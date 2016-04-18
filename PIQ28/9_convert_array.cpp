
/**
    Convert Array
    Given an array [a1, a2, …, aN, b1, b2, …, bN, c1, c2, …, cN]  convert it to [a1, b1, c1, a2, b2, c2, …,
    aN, bN, cN] in­place using constant extra space
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

void _swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

vector<int> convertArray1( vector<int> &arr) {
    vector<int> res;
    if(arr.size()%3 != 0) return res;
    res.resize(arr.size());

    int len = arr.size() / 3;
    int size = arr.size();
    for(int i = 0; i < size; i++) {
        res[i] = arr[i/3 + (i%3)*len];
    }

    return res;
}

void convertArray2(vector<int> &arr) {
    if(arr.size()%3 != 0) return;

    int len = arr.size() / 3;
    int size = arr.size();
    for(int i = 0; i < size; i++) {
        int swapIndex = i/3 + (i%3)*len;
        while(swapIndex < i) {
            swapIndex = swapIndex/3 + (swapIndex%3)*len;
        }
        _swap(arr[i], arr[swapIndex]);
    }
}

int main() {

    vector<int> arr = {1,2,3,4,5,6,7,8,9};
    convertArray2(arr);

    for (auto x : arr) {
        std::cout << x << std::endl ;
    }

    return 0;
}
