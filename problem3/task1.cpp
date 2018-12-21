#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

using lock_t = std::lock_guard<std::mutex>;

int main() {
    std::atomic<size_t> count { 0 };
    std::atomic<bool> done { false };
    std::mutex qmutex;
    std::queue<int> items;

    std::thread producer([&]() {
        for (int i = 0; i < 10000; ++i) {
            // ... some code may be here ...
            lock_t lck(qmutex);
            items.push(i);
            count++;
        }
        done.store(true);
    });

    std::thread consumer([&]() {
        while (!done.load()) {
            lock_t lck(qmutex);
            while (!items.empty()) {
                items.pop();
                // ...
                count--;
            }
        }
    });

    producer.join();
    consumer.join();
    std::cout << count << std::endl;
}

