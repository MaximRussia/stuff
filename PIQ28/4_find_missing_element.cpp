
/**
    Find Missing Element.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

/// This solution is also O(N)
int findMissingElement1(vector<int> &v1, vector<int> &v2) {
	int x = 0;
	for (int i = 0; i < v1.size(); ++i) {
		x ^= v1[i];
	}
	for (int i = 0; i < v2.size(); ++i) {
		x ^= v2[i];
	}
	return x;
}

/// find minimal missing element
int findMissingElement3(vector<int> &v1) {
	int x = 0;
	for (int i = 0; i < v1.size(); ++i) {
		x ^= v1[i];
	}
	return x;
}

int findMissingElement2(vector<int> &v1, vector<int> &v2) {
    map<int, int> hash;
    for(int i = 0; i < v1.size(); i++) {
        hash[v1[i]] = 1;
    }

    for(int i = 0; i < v2.size(); i++) {
        if(hash.find(v2[i]) == hash.end()) return v2[i];
    }

    return -1;
}


int main() {

    vector<int> v1 = {1,2,3,4,5,6};
    vector<int> v2 = {1,2,3,4,0,6};

    cout << findMissingElement2(v1, v2) << endl;

    return 0;
}
