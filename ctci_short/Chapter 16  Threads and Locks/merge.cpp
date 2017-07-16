#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <future>
#include <algorithm>
using namespace std;

template<typename Iter>
void mergesort_mt1(Iter begin, Iter end,
	unsigned int N = std::thread::hardware_concurrency()) {
	auto len = std::distance(begin, end);
	if (len < 2)
		return;

	Iter mid = std::next(begin, len / 2);
	if (N > 1) {
		auto fn = std::async(mergesort_mt1<Iter>, begin, mid, N - 2);
		mergesort_mt1(mid, end, N - 2);
		fn.wait();
	} else {
		mergesort_mt1(begin, mid, 0);
		mergesort_mt1(mid, end, 0);
	}

	std::inplace_merge(begin, mid, end);
}

template<typename Iter>
void mergesort_mt2(Iter begin, Iter end,
	unsigned int N = std::thread::hardware_concurrency()) {
	auto len = std::distance(begin, end);
	if (len <= 1024) {
		std::sort(begin, end);
		return;
	}

	Iter mid = std::next(begin, len / 2);
	if (N > 1) {
		auto fn = std::async(mergesort_mt2<Iter>, begin, mid, N - 2);
		mergesort_mt2(mid, end, N - 2);
		fn.wait();
	} else {
		mergesort_mt2(begin, mid, 0);
		mergesort_mt2(mid, end, 0);
	}

	std::inplace_merge(begin, mid, end);
}

template<typename Iter>
void mergesort_mt3(Iter begin, Iter end,
	unsigned int N = std::thread::hardware_concurrency()) {
	auto len = std::distance(begin, end);
	if (len <= 1024 || N < 2) {
		std::sort(begin, end);
		return;
	}

	Iter mid = std::next(begin, len / 2);
	auto fn = std::async(mergesort_mt3<Iter>, begin, mid, N - 2);
	mergesort_mt3(mid, end, N - 2);
	fn.wait();
	std::inplace_merge(begin, mid, end);
}

int main() {
	using namespace std::chrono;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

	std::vector<unsigned int> v, back(9999999);

	std::cout << "Generating...\n";
	std::generate_n(back.begin(), back.size(), [&]() {return dist(rng); });

	time_point<system_clock> t0, t1;

	v = back;
	std::cout << "std::sort: ";
	t0 = system_clock::now();
	std::sort(v.begin(), v.end());
	t1 = system_clock::now();
	std::cout << duration_cast<milliseconds>(t1 - t0).count() << "ms\n";

	v = back;
	std::cout << "mergesort_mt1: ";
	t0 = system_clock::now();
	mergesort_mt1(v.begin(), v.end());
	t1 = system_clock::now();
	std::cout << duration_cast<milliseconds>(t1 - t0).count() << "ms\n";

	v = back;
	std::cout << "mergesort_mt2: ";
	t0 = system_clock::now();
	mergesort_mt2(v.begin(), v.end());
	t1 = system_clock::now();
	std::cout << duration_cast<milliseconds>(t1 - t0).count() << "ms\n";

	v = back;
	std::cout << "mergesort_mt3: ";
	t0 = system_clock::now();
	mergesort_mt3(v.begin(), v.end());
	t1 = system_clock::now();
	std::cout << duration_cast<milliseconds>(t1 - t0).count() << "ms\n";

	return 0;
}
