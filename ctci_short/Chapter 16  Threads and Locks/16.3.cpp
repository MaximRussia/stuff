#include <mutex>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

std::mutex cout_mutex;

struct fork {
    fork(){};
    std::mutex m;
};

struct philosopher {
    std::string name;
    size_t left;
    size_t right;

    philosopher(const std::string &name_, size_t left_, size_t right_)
        : name(name_), left(left_), right(right_){}

    void eat(std::vector<fork> &table_)
    {
        {
            std::unique_lock<std::mutex>  cout_lock(cout_mutex);
            std::cout << "begin from " << std::this_thread::get_id() << std::endl;
        }

        std::unique_lock<std::mutex> l(table_[left].m);
        std::unique_lock<std::mutex> r(table_[right].m);

        {
            std::unique_lock<std::mutex>  cout_lock(cout_mutex);
            std::cout << name << " is eating.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::unique_lock<std::mutex>  cout_lock(cout_mutex);
            std::cout << name << " is done eating.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::unique_lock<std::mutex>  cout_lock(cout_mutex);
            std::cout << "end from " << std::this_thread::get_id() << std::endl;
        }
    }
};

int main()
{
    const int THREAD = 5;
    std::vector<fork> table(THREAD);
    std::vector<philosopher> philosophers;
    philosophers.emplace_back("Judith", 0, 1);
    philosophers.emplace_back("Gilles", 1, 2);
    philosophers.emplace_back("Karl  ", 2, 3);
    philosophers.emplace_back("Emma  ", 3, 4);
    philosophers.emplace_back("Michel", 0, 4);

    std::vector<std::thread> handles(THREAD);

    for (auto i = 0; i < THREAD; ++i) {
        handles[i] = std::thread(&philosopher::eat, &philosophers[i], std::ref(table));
    }

    for (auto i = 0; i < THREAD; ++i) {
        handles[i].join();
    }
}
