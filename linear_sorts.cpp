#include <random>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <limits>

//Chrono typedefs
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

static const std::size_t MAX_VALUE = 5000000;

void fill_random(std::vector<std::size_t>& vec) {
    std::mt19937 generator;
    std::uniform_int_distribution<std::size_t> distribution(0, MAX_VALUE);

    for (std::size_t i = 0; i < MAX_VALUE; ++i) {
        vec.push_back(distribution(generator));
    }
}

void std_sort(std::vector<std::size_t>& A) {
    std::sort(A.begin(), A.end());
}

void counting_sort(std::vector<std::size_t>& A) {
    std::vector<std::size_t> C(MAX_VALUE + 1, 0);

    for (std::size_t i = 0; i < A.size(); ++i) {
        ++C[A[i]];
    }

    int current = 0;
    for (std::size_t i = 0; i < C.size(); ++i) {
        for (std::size_t j = 0; j < C[i]; ++j) {
            A[current++] = i;
        }
    }
}

void bucket_sort(std::vector<std::size_t>& A) {
    std::vector<std::vector<std::size_t>> B(MAX_VALUE + 1);

    for (std::size_t i = 0; i < A.size(); ++i) {
        B[A[i]].push_back(A[i]);
    }

    std::size_t current = 0;
    for (std::size_t i = 0; i < B.size(); ++i) {
        for (auto item : B[i]) {
            A[current++] = item;
        }
    }
}

//For radix sort
static const std::size_t digits = 2;        //Digits
static const std::size_t r = 16;            //Bits
static const std::size_t radix = 1 << r;    //Bins
static const std::size_t mask = radix - 1;

void radix_sort(std::vector<std::size_t>& A) {
    std::vector<std::size_t> B(MAX_VALUE);
    std::vector<std::size_t> cnt(radix);

    for (std::size_t i = 0, shift = 0; i < digits; i++, shift += r) {
        for (std::size_t j = 0; j < radix; ++j) {
            cnt[j] = 0;
        }

        for (std::size_t j = 0; j < B.size(); ++j) {
            ++cnt[(A[j] >> shift) & mask];
        }

        for (std::size_t j = 1; j < radix; ++j) {
            cnt[j] += cnt[j - 1];
        }

        for (long j = B.size() - 1; j >= 0; --j) {
            B[--cnt[(A[j] >> shift) & mask]] = A[j];
        }

        for (std::size_t j = 0; j < B.size(); ++j) {
            A[j] = B[j];
        }
    }
}

template<typename Function>
void bench(Function sort_function) {
    std::vector<std::size_t> vec;
    fill_random(vec);

    Clock::time_point t0 = Clock::now();
    sort_function(vec);
    Clock::time_point t1 = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);

    std::cout << ms.count() << " ms" << std::endl;
}

int main() {
    std::cout << "std::sort" << std::endl;
    bench(&std_sort);

    std::cout << "counting_sort" << std::endl;
    bench(&counting_sort);

    std::cout << "bucket_sort" << std::endl;
    bench(&::bucket_sort);

    std::cout << "radix_sort" << std::endl;
    bench(&radix_sort);

    return 0;
}
