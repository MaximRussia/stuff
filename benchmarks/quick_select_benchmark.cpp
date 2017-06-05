
/***
Find kth Smallest using Quick Select O(n) vs QuickSort O(NlogN)
***/

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

LARGE_INTEGER _timer_start;
LARGE_INTEGER _timer_stop;
LARGE_INTEGER _timer_frequency;
bool _timer_init = QueryPerformanceFrequency(&_timer_frequency);
#define TICK() if( _timer_init == false ) { \
	cout << "Failed to query the performance frequency." << endl; \
	cout << "Please do not use timer.h" << endl; \
	exit(1); \
} \
	QueryPerformanceCounter(&_timer_start);
#define TOCK() QueryPerformanceCounter(&_timer_stop);
#define TICK_ELAPSED() (_timer_stop.QuadPart - _timer_start.QuadPart)
#define DURATION() ( TICK_ELAPSED() / (double) _timer_frequency.QuadPart)
//------------------------------------------------------------------------------------------------------------------

int partition(int* A, int left, int right) {
	int pivot = A[right];

	while (left <= right) {
		while (A[left] < pivot) {
			left++;
		}
		while (A[right] > pivot) {
			right--;
		}
		if (A[left] == A[right]) {
			left++;
		} else if (left < right) {
			swap(A[left], A[right]);
		}
	}
	return right;
}

int quick_select(int* A, int left, int right, int k) {
	if (left == right) {
		return A[left];
	}

	int pivot = partition(A, left, right);
	int length = pivot - left + 1;

	if (length == k) {
		return A[pivot];
	} else if (k < length) {
		return quick_select(A, left, pivot - 1, k);
	} else {
		return quick_select(A, pivot + 1, right, k - length);
	}
}

void quick_sort(int* A, int left, int right) {
	if (left < right) {
		int pivot = partition(A, left, right);
		quick_sort(A, left, pivot - 1);
		quick_sort(A, pivot + 1, right);
	}
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

	TICK();
	cout << "The Value of " << k << "-th smallest element in QuickSelect is : " << quick_select(A, 0, inputsize - 1, k) << endl;
	TOCK();
	//Show duration
	cout << "Duration (QuickSelect): " << DURATION() << " seconds" << endl;
	cout << endl << endl;

	TICK();
	quick_sort(A, 0, inputsize - 1);
	cout << "The Value of " << k << "-th smallest element in QuickSort is : " << A[k - 1] << endl;;
	TOCK();
	//Show duration
	cout << "Duration (QuickSort): " << DURATION() << " seconds" << endl;
}
