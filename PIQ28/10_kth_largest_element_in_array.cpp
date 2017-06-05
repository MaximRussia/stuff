
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

int kth_largest_element1(vector<int> arr, int k) {
	sort(arr.begin(), arr.end());
	return arr[k - 1];
}

void _swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

/**
Find swapIndex
**/
int partition2(vector<int> &arr, int left, int right, int pivot) {
	int pivotValue = arr[pivot];
	/* Put the pivot value at the end */
	_swap(arr[pivot], arr[right]);
	int storePosition = left;
	for (int i = left; i < right; i++) {
		if (arr[i] < pivotValue) {
			_swap(arr[i], arr[storePosition]);
			storePosition++;
		}
	}
	_swap(arr[storePosition], arr[right]);
	return storePosition;
}

int kth_largest_element2(vector<int> &arr, int k) {
	int left = 0;
	int right = arr.size();
	while (true) {
		int pivotIndex = (left + right) / 2;
		int newPivot = partition2(arr, left, right, pivotIndex);
		if (newPivot == k)
			return arr[newPivot];
		else if (newPivot < k)
			left = newPivot + 1;
		else
			right = newPivot - 1;
	}
}

int main() {

	vector<int> arr = { 3, 1, 2, 1, 4 };
	std::cout << kth_largest_element1(arr, 3) << std::endl;
	std::cout << kth_largest_element2(arr, 3) << std::endl;

	return 0;
}
