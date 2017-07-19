
/***
Find kth Smallest using Quick Select O(n) vs QuickSort O(NlogN)
***/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

// Partition using Lomuto partition scheme
int partition(int a[], int left, int right, int pivotIndex)
{
	// Pick pivotIndex as pivot from the array
	int pivot = a[pivotIndex];

	// Move pivot to end
	swap(a[pivotIndex], a[right]);

	// elements less than pivot will be pushed to the left of pIndex
	// elements more than pivot will be pushed to the right of pIndex
	// equal elements can go either way
	int pIndex = left;
	int i;

	// each time we finds an element less than or equal to pivot, pIndex
	// is incremented and that element would be placed before the pivot.
	for (i = left; i < right; i++) {
		if (a[i] <= pivot) {
			swap(a[i], a[pIndex]);
			pIndex++;
		}
	}

	// Move pivot to its final place
	swap(a[pIndex], a[right]);

	// return pIndex (index of pivot element)
	return pIndex;
}

// Returns the k-th smallest element of list within left..right inclusive
// (i.e. left <= k <= right).
// The search space within the array is changing for each round - but the list
// is still the same size. Thus, k does not need to be updated with each round.
int quickSelect(int A[], int left, int right, int k) {
	// If the array contains only one element, return that element
	if (left == right)
		return A[left];

	// select a pivotIndex between left and right
	int pivotIndex = (left + right - 1) / 2;

	pivotIndex = partition(A, left, right, pivotIndex);

	// The pivot is in its final sorted position
	if (k == pivotIndex)
		return A[k];

	// if k is less than the pivot index
	else if (k < pivotIndex)
		return quickSelect(A, left, pivotIndex - 1, k);

	// if k is more than the pivot index
	else
		return quickSelect(A, pivotIndex + 1, right, k);
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
	cout << "The Value of " << k << "-th smallest element in QuickSelect is : " << quickSelect(A, 0, inputsize - 1, k) << endl;
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
