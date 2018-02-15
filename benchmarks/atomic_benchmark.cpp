
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <cmath>
#include <ctime>
using namespace std;

#define OPERATIONS 999
#define REPEAT 5

void bench_lock(int Threads) {
	std::mutex mutex;

	time_t t1 = clock();

	for (int i = 0; i < REPEAT; ++i) {
		std::vector<std::thread> threads;
		float counter = 0.0f;

		for (int i = 0; i < Threads; ++i) {
			threads.push_back(std::thread([&]() {
				for (int i = 0; i < OPERATIONS; ++i) {
					mutex.lock();
					counter += pow(i, pow(i, 60));
					mutex.unlock();
				}
			}));
		}

		for (auto& thread : threads) {
			thread.join();
		}
	}

	time_t t2 = clock();

	std::cout << "lock with " << Threads << " threads, ms = " << float(t2 - t1) / CLOCKS_PER_SEC << std::endl;
}

void bench_lock_guard(int Threads) {
	std::mutex mutex;

	time_t t1 = clock();

	for (int i = 0; i < REPEAT; ++i) {
		float counter = 0.0f;

		std::vector<std::thread> threads;

		for (int i = 0; i < Threads; ++i) {
			threads.push_back(std::thread([&]() {
				for (int i = 0; i < OPERATIONS; ++i) {
					std::lock_guard<std::mutex> guard(mutex);
					counter += pow(i, pow(i, 60));
				}
			}));
		}

		for (auto& thread : threads) {
			thread.join();
		}
	}

	time_t t2 = clock();

	std::cout << "lock_guard with " << Threads << " threads, ms = " << float(t2 - t1) / CLOCKS_PER_SEC << std::endl;
}

void bench_atomic(int Threads) {

	time_t t1 = clock();

	for (int i = 0; i < REPEAT; ++i) {
		std::atomic<float> counter;
		counter.store(0.0f);

		std::vector<std::thread> threads;

		for (int i = 0; i < Threads; ++i) {
			threads.push_back(std::thread([&]() {
				for (int i = 0; i < OPERATIONS; ++i) {
					counter.store(pow(i, pow(i, 60)));
				}
			}));
		}

		for (auto& thread : threads) {
			thread.join();
		}
	}

	time_t t2 = clock();

	std::cout << "atomic with " << Threads << " threads, ms = " << float(t2 - t1) / CLOCKS_PER_SEC << std::endl;
}

void bench_spin(int Threads) {

	class SpinLock {
		std::atomic_flag locked = ATOMIC_FLAG_INIT;
	public:
		void lock() {
			while (locked.test_and_set(std::memory_order_acquire)) { ; }
		}
		void unlock() {
			locked.clear(std::memory_order_release);
		}
	};

	class SpinLockRAII {
		SpinLock& lock;

	public:
		SpinLockRAII(SpinLock& _lock) : lock(_lock) {
			lock.lock();
		}

		~SpinLockRAII() {
			lock.unlock();
		}
	};

	SpinLock mutex;

	time_t t1 = clock();

	for (int i = 0; i < REPEAT; ++i) {
		float counter = 0.0f;

		std::vector<std::thread> threads;

		for (int i = 0; i < Threads; ++i) {
			threads.push_back(std::thread([&]() {
				for (int i = 0; i < OPERATIONS; ++i) {
					SpinLockRAII guard(mutex);
					counter += pow(i, pow(i, 60));
				}
			}));
		}

		for (auto& thread : threads) {
			thread.join();
		}
	}

	time_t t2 = clock();

	std::cout << "spin_lock with " << Threads << " threads, ms = " << float(t2 - t1) / CLOCKS_PER_SEC << std::endl;

}

#define bench(name)\
	name(1); \
	name(4); \
	name(16); \
	name(64); \
	name(256);

int main() {

	int threads = std::thread::hardware_concurrency();

	cout << "MAX THREADS : " << threads << endl;

	bench(bench_atomic);
	bench(bench_lock);
	bench(bench_lock_guard);
	bench(bench_spin);

	return 0;
}
