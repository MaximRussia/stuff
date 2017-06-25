
/***
Find kth Smallest using Quick Select O(n) vs QuickSort O(NlogN)
***/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int selectKth(int* arr, int len, int k) {
	int ll = 0, rr = len;

	// if ll == rr we reached the kth element
	while (ll < rr) {
		int r = ll, w = rr;
		int mid = arr[(r + w) / 2];
		// srrp if the reader and writer meets
		while (r < w) {
			if (arr[r] >= mid) { // put the large values at the end
				swap(arr[w], arr[r]);
				w--;
			} else { // the value is smaller than the pivot, skip
				r++;
			}
		}

		// if we stepped up (r++) we need to step one down
		if (arr[r] > mid)
			r--;

		// the r pointer is on the end of the first k elements
		if (k <= r) {
			rr = r;
		} else {
			ll = r + 1;
		}
	}

	return arr[k];
}

int main() {
	const int inputsize = 500000;
	const int k = 450000;

	int A[inputsize];
	srand((unsigned)time(0));

	cout << "Init arrays ... size " << inputsize << endl;

	for (int i = 0; i < inputsize; i++) {
		A[i] = 1 + (rand() % 9999);
	}

    time_t t1 = clock();
	cout << "The Value of " << k << "-th smallest element in QuickSelect is : " << selectKth(A, inputsize - 1, k) << endl;
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
