
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <ctime>
using namespace std;

template<class T>
void parallel_sort(T * data, int len, int threads = 1) {
	if (len < threads) {
		std::sort(data, data + len, std::less<T>());
        return;
	}

	auto future = std::async(parallel_sort<T>, data, len / 2, threads);
	parallel_sort(data + len / 2, len / 2, threads);
	future.wait();
	std::inplace_merge(data, data + len / 2, data + len, std::less<T>());
}

int main() {

	const int NUM = 999999;

	srand(time(0));
	vector<int> arr;
	for (int i = 0; i < NUM; i++) {
		arr.push_back(rand() % NUM);
	}

	{
		time_t t1 = clock();
		parallel_sort(&arr[0], arr.size(), std::thread::hardware_concurrency());
		time_t t2 = clock();
		cout << float(t2 - t1) / CLOCKS_PER_SEC << endl;
	}

	{
		time_t t1 = clock();
		parallel_sort(&arr[0], arr.size());
		time_t t2 = clock();
		cout << float(t2 - t1) / CLOCKS_PER_SEC << endl;
	}


	return 0;
}
