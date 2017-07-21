
/**
	Kth Largest Element in Array
	Given an array of integers find the kth element in the sorted order (not the kth distinct element).
	So, if the array is [3, 1, 2, 1, 4] and k is 3 then the result is 2, because it’s the 3rd element in sorted
	order (but the 3rd distinct element is 3).
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

/**
Find swapIndex
**/
int partition(vector<int> &arr, int left, int right) {

    int mid = (left + right) / 2;
	int mid_value = arr[mid];
	/* Put the mid value at the end */
	std::swap(arr[mid], arr[right]);
	int result = left;
	for (int i = left; i <= right; i++) {
		if (arr[i] < mid_value) {
			std::swap(arr[i], arr[result]);
			result++;
		}
	}
	std::swap(arr[result], arr[right]);
	return result;
}

int QuickSelect(vector<int> &arr, int k) {
	int l = 0;
	int r = arr.size();
	while (l <= r) {
		int pivot = partition(arr, l, r);
		if (pivot == k)
			return arr[k];
		else if (pivot < k)
			l = pivot + 1;
		else
			r = pivot - 1;
	}

	return INT_MIN;
}

int main() {

	vector<int> arr = { 5,3,4,2,1 };
	std::cout << QuickSelect(arr, 0) << std::endl;
	std::cout << QuickSelect(arr, 1) << std::endl;
	std::cout << QuickSelect(arr, 2) << std::endl;
	std::cout << QuickSelect(arr, 3) << std::endl;
	std::cout << QuickSelect(arr, 4) << std::endl;

	return 0;
}
