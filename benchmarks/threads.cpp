
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;

template<class T>
class Singleton {
public:
    static T* GetInstance() {
        static T* m_pInstance;

        if (!m_pInstance)
            m_pInstance = new T();
        return m_pInstance;
    }

    Singleton() {}
    virtual ~Singleton() {delete GetInstance();}


private:
    Singleton(const T&);
    Singleton& operator=(const T&);
};

class TestClass : public Singleton<TestClass> {
private:
    vector<int> v;

public:
    TestClass(){v.push_back(0);}
    virtual ~TestClass(){}
    int GetA() { for(auto &i : v) { cout << i << " "; } cout << endl; }
    void AddA() { v.push_back(v.back()+1); }
};

template<class T>
class SingletonThreadSafe {
public:
    static T* GetInstance() {
        static std::atomic<T*> m_instance;
        static std::mutex m_mutex;
        T* tmp = m_instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);

        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new T();
                std::atomic_thread_fence(std::memory_order_release);
                m_instance.store(tmp, std::memory_order_relaxed);
            }
        }
        return tmp;
    }

    SingletonThreadSafe() {}
    virtual ~SingletonThreadSafe() {delete GetInstance();}


private:
    SingletonThreadSafe(const T&);
    SingletonThreadSafe& operator=(const T&);
};

class TestClassThreadSafe : public SingletonThreadSafe<TestClassThreadSafe> {
private:
    vector<int> v;

public:
    TestClassThreadSafe(){ v.push_back(0); }
    virtual ~TestClassThreadSafe(){}
    int GetA() { for(auto &i : v) { cout << i << " "; } cout << endl; }
    void AddA() { v.push_back(v.back()+1); }
};

#ifndef TEST_CLASS
    #define TEST_CLASS (TestClass::GetInstance())
#endif


#ifndef TEST_CLASS_THREAD
    #define TEST_CLASS_THREAD (TestClassThreadSafe::GetInstance())
#endif

void call_from_thread() {
    TEST_CLASS->AddA();
}

void call_from_thread_safe() {

    TEST_CLASS_THREAD->AddA();
}

int main() {

    vector<thread> threads;

    for(int i = 0; i < 100; i++) {
        threads.push_back(thread(call_from_thread));
        threads.push_back(thread(call_from_thread_safe));
    }

    for(int i = 0; i < 200; i++) {
        threads[i].join();
    }

    TEST_CLASS->GetA();
    TEST_CLASS_THREAD->GetA();

    return 0;

}
