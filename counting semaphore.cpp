#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0) : count(count) {}

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0) {
            cv.wait(lock);
        }
        count--;
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

std::mutex coutMutex; // Mutex for synchronized output

void critical_section(int thread_id, Semaphore& semaphore) {
    semaphore.wait(); // Enter critical section

    // Start of critical section
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << thread_id << " is entering the critical section." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work in the critical section
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << thread_id << " is leaving the critical section." << std::endl;
    }
    // End of critical section

    semaphore.signal(); // Leave critical section
}

int main() {
    int num_threads, initial_count;

    // Get user input
    std::cout << "Enter the number of threads: ";
    std::cin >> num_threads;
    std::cout << "Enter the initial semaphore count: ";
    std::cin >> initial_count;

    Semaphore semaphore(initial_count);
    std::vector<std::thread> threads;

    // Create and start threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(critical_section, i, std::ref(semaphore));
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
