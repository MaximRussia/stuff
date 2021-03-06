#include <atomic>
#include <future>
#include <thread>
#include <iostream>
#include <vector>
using namespace std;

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

struct fork {
    fork(){}
    SpinLock spin_mtx;
    mutex mtx;
};

mutex out;

void eat(vector<fork> & f, int l, int r) {
    /// asm("LOCK")
    /// unique_lock<mutex> lk1(f[l].mtx);
    /// unique_lock<mutex> lk2(f[r].mtx);
    SpinLockRAII lk1(f[l].spin_mtx);
    SpinLockRAII lk2(f[r].spin_mtx);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        unique_lock<mutex> lk_out(out);
        cout << "eating ... " << l << " " << r << endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        unique_lock<mutex> lk_out(out);
        cout << "finish ... " << l << " " << r << endl;
    }
}

int main() {

    vector<fork> f(6);

    vector<thread> t;
    t.push_back(thread(&eat, ref(f), 0, 1));
    t.push_back(thread(&eat, ref(f), 1, 2));
    t.push_back(thread(&eat, ref(f), 2, 3));
    t.push_back(thread(&eat, ref(f), 3, 4));
    t.push_back(thread(&eat, ref(f), 4, 5));
    t.push_back(thread(&eat, ref(f), 5, 0));

    for(int i = 0; i < t.size(); i++) {
        t[i].join();
    }

    return 0;
}
