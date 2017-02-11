#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

mutex m;

void merge_t(vector<int> &A, long l, long mid, long r) {

    unique_lock<mutex> lock(m);

	long ll = l;
	long size = r - l + 1;
	long rr = mid + 1;
	vector<int> temp;

	while (ll <= mid && rr <= r) {
		if (A[ll] < A[rr])
			temp.push_back(A[ll++]);
		else
			temp.push_back(A[rr++]);
	}

	while (ll <= mid)
		temp.push_back(A[ll++]);

	while (rr <= r)
		temp.push_back(A[rr++]);

	for (int i = 0; i < size; i++)
		A[l + i] = temp[i];
}

void merge_sort_t_parallel(vector<int> &A, long l, long r) {
	if (l >= r) return;

	int mid = l + (r - l) / 2;

	// multi-thread version
	thread first(merge_sort_t_parallel, std::ref(A), l, mid);
	thread second(merge_sort_t_parallel, std::ref(A), mid + 1, r);
	first.join();
	second.join();

	thread third(merge_t, std::ref(A), l, mid, r);
	third.join();
}

void merge_sort_t(vector<int> &A, long l, long r) {
	if (l >= r) return;

	int mid = l + (r - l) / 2;

	// multi-thread version
	thread first(merge_sort_t, std::ref(A), l, mid);
	thread second(merge_sort_t, std::ref(A), mid + 1, r);
	first.join();
	second.join();

	merge_t(A, l, mid, r);
}

void func() {
    unique_lock<mutex> lock(m);
    for(int i = 0; i < INT_MAX; i++) {}
}

int main() {

     {
        vector<int> vec;

        for(int i = 400; i >= 0; i--) {
            vec.push_back(i);
        }

        auto t1 = clock();
        merge_sort_t(vec, 0, vec.size()-1);
        auto t2 = clock();
        cout << (t2 - t1) / 1000.0 << endl;
    }

    {
        vector<int> vec;

        for(int i = 400; i >= 0; i--) {
            vec.push_back(i);
        }

        auto t1 = clock();
        merge_sort_t_parallel(vec, 0, vec.size()-1);
        auto t2 = clock();
        cout << (t2 - t1) / 1000.0 << endl;
    }

    {
        auto t1 = clock();
        func();
        func();
        auto t2 = clock();
        cout << (t2 - t1) / 1000.0 << endl;
    }

    {
        auto t1 = clock();
        thread first(func);
        thread second(func);
        first.join();
        second.join();
        auto t2 = clock();
        cout << (t2 - t1) / 1000.0 << endl;
    }

	return 0;
}
