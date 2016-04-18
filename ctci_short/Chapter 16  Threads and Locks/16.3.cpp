
/**

**/



/**
    HINTS:
    1 philosopher use 1 and 5 forks
    2 philosopher use 1 and 2 forks
    3 philosopher use 2 and 3 forks
    4 philosopher use 3 and 4 forks
    5 philosopher use 4 and 5 forks
**/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class Chopstick {
public:
    Chopstick(){};
    mutex m;
};

int main() {
    auto eat = [](Chopstick* leftChopstick, Chopstick* rightChopstick, int philosopherNumber, int leftChopstickNumber, int rightChopstickNumber) {
        if (leftChopstick == rightChopstick)
            throw ("Left and right chopsticks should not be the same!");

        lock(leftChopstick->m, rightChopstick->m);                // ensures there are no deadlocks

        lock_guard<mutex> a(leftChopstick->m, adopt_lock);
        cout <<  "   Philosopher " + std::string(1, '0' + philosopherNumber) + " picked " + std::string(1, '0' + leftChopstickNumber) + " chopstick.\n";

        lock_guard<mutex> b(rightChopstick->m, adopt_lock);
        cout << "   Philosopher " + std::string(1, '0' + philosopherNumber) + " picked " + std::string(1, '0' + rightChopstickNumber) + " chopstick.\n";

        cout << "Philosopher " +  std::string(1, '0' + philosopherNumber) + " eats.\n";

        std::chrono::milliseconds timeout(1400);
        std::this_thread::sleep_for(timeout);
    };

    static const int numPhilosophers = 5;

    // 5 utencils on the left and right of each philosopher. Use them to acquire locks.
    vector< Chopstick* > chopsticks(numPhilosophers);
    for (int i = 0; i < numPhilosophers; ++i) {
        chopsticks[i] = new Chopstick();
    }

    // This is where we create philosophers, each of 5 tasks represents one philosopher.
    vector<thread> tasks(numPhilosophers);

    tasks[0] = thread(eat,
            chopsticks[0],                          // left chopstick:  #1
            chopsticks[numPhilosophers - 1],        // right chopstick: #5
            0 + 1,                                        // philosopher number
            1,                                            // left Chopstick Number
            numPhilosophers                               // right Chopstick Number
        );

    for (int i = 1; i < numPhilosophers; ++i) {
        tasks[i] = (thread(eat,
                chopsticks[i - 1],                  // left chopstick
                chopsticks[i],                      // right chopstick
                i + 1,                                    // philosopher number
                i,                                        // left Chopstick Number
                i + 1                                     // right Chopstick Number
                )
            );
    }

    // May eat!
    for_each(tasks.begin(), tasks.end(), mem_fn(&thread::join));

    for(auto data : chopsticks) { delete data; data = nullptr; }
    chopsticks.clear();

    return 0;
}
