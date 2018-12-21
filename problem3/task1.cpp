#include <iostream>
#include <thread>
#include <queue>

int main() {
    size_t count = 0;
    bool done = false;
    std::queue<int> items;
    std::thread producer([&]() {
        for (int i = 0; i < 10000; ++i) {
        // ... some code may be here ...
            items.push(i);
            count++;
        }
        done = true;
    });

    std::thread consumer([&]() {
        while (!done) {
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

