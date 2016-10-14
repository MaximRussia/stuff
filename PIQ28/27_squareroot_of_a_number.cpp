/**
	Squareroot of a Number
	Find the squareroot of a given number rounded down to the nearest integer, without using the
	sqrt function. For example, squareroot of a number between [9, 15] should return 3, and [16, 24]
	should be 4.
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

int floor_sqrt(int x) {
	int left = 0;
	int right = x / 2;

	while (left <= right) {
		int mid = (left + right) / 2;
		int mid_mid = mid*mid;
		if (mid_mid == x) return mid;
		if (mid_mid < x) left++;
		else right--;
	}

	return left - 1; /// return left;
}

int main() {

	cout << floor_sqrt(13) << endl;

	return 0;
}
