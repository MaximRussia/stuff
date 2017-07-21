
/***
Find kth Smallest using Quick Select O(n) vs QuickSort O(NlogN)
***/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <ctime>
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
	const int inputsize = 500000;
	const int k = 450000;

	vector<int> A;
	srand((unsigned)time(0));

	cout << "Init arrays ... size " << inputsize << endl;

	for (int i = 0; i < inputsize; i++) {
		A.push_back(1 + (rand() % 9999));
	}

    time_t t1 = clock();
	cout << "The Value of " << k << "-th smallest element in QuickSelect is : " << QuickSelect(A, k) << endl;
    time_t t2 = clock();
	//Show duration
	cout << "Duration (QuickSelect): " << float(t2 - t1) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << endl << endl;

	t1 = clock();
	std::sort(std::begin(A), std::end(A));
	t2 = clock();
	cout << "The Value of " << k << "-th smallest element in QuickSort is : " << A[k - 1] << endl;;
	//Show duration
	cout << "Duration (QuickSort): " << float(t2 - t1) / CLOCKS_PER_SEC << " seconds" << endl;
}
