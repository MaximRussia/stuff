
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <cmath>
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


#define OPERATIONS 999
#define REPEAT 5

void bench_lock(int Threads) {
	std::mutex mutex;

	TICK();

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

	TOCK();

	std::cout << "lock with " << Threads << " threads, ms = " << DURATION() << std::endl;
}

void bench_lock_guard(int Threads) {
	std::mutex mutex;

	TICK();

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

	TOCK();

	std::cout << "lock_guard with " << Threads << " threads, ms = " << DURATION() << std::endl;
}

void bench_atomic(int Threads) {
	TICK();

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

	TOCK();

	std::cout << "atomic with " << Threads << " threads, ms = " << DURATION() << std::endl;
}

#define bench(name)\
	name(1); \
	name(2); \
	name(4); \
	name(8); \
	name(16); \
	name(32); \
	name(64); \
	name(128);

int main() {

	int threads = std::thread::hardware_concurrency();

	cout << "MAX THREADS : " << threads << endl;

	bench(bench_atomic);
	bench(bench_lock);
	bench(bench_lock_guard);

	return 0;
}
