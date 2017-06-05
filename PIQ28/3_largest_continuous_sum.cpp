
/**
	Given an array of integers (positive and negative) find the largest continuous sum.
	**/

/*
	The time complexity is O(N) and space complexity is O(1), which are both optimal.
	*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

int largestContSumm(vector<int> &v) {
	if (v.empty()) return 0;

	int summ = 0, curr = 0, prev = 0;
	for (int i = 0; i < v.size(); i++) {
		curr += v[i];
		if (curr >= prev) {
			summ = curr;
		} else {
			curr = 0;
		}
		prev = curr;
	}
	return summ;
}

int main() {

	vector<int> v = { 1, 2, 3, 4, -6, 7, 7, 7 };

	cout << largestContSumm(v) << endl;

	return 0;
}
