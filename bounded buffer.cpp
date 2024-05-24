#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

class BoundedBuffer {
public:
    BoundedBuffer(int size) : size(size) {}

    void produce(int item) {
        unique_lock<mutex> lock(mtx);
        cond_producer.wait(lock, [this]() { return buffer.size() < size; });

        buffer.push(item);
        cout << "Produced: " << item << "\n";

        cond_consumer.notify_one();
    }

    int consume() {
        unique_lock<mutex> lock(mtx);
        cond_consumer.wait(lock, [this]() { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << "\n";

        cond_producer.notify_one();
        return item;
    }

private:
    queue<int> buffer;
    int size;
    mutex mtx;
    condition_variable cond_producer;
    condition_variable cond_consumer;
};

void producer(BoundedBuffer& buffer, int id, int itemsToProduce) {
    for (int i = 0; i < itemsToProduce; i++) {
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
        buffer.produce(id * 1+ i); // Produce unique items
    }
}

void consumer(BoundedBuffer& buffer, int itemsToConsume) {
    for (int i = 0; i < itemsToConsume; i++) {
        this_thread::sleep_for(chrono::milliseconds(500)); // Simulate work
        buffer.consume();
    }
}

int main() {
    int bufferSize, numProducers, numConsumers, itemsToProduce;

    cout << "Enter buffer size: ";
    cin >> bufferSize;
    cout << "Enter number of producers: ";
    cin >> numProducers;
    cout << "Enter number of consumers: ";
    cin >> numConsumers;
    cout << "Enter number of items each producer should produce: ";
    cin >> itemsToProduce;

    BoundedBuffer buffer(bufferSize);

    vector<thread> producers, consumers;
    int totalItemsToConsume = numProducers * itemsToProduce / numConsumers;

    for (int i = 0; i < numProducers; i++) {
        producers.push_back(thread(producer, ref(buffer), i + 1, itemsToProduce));
    }

    for (int i = 0; i < numConsumers; i++) {
        consumers.push_back(thread(consumer, ref(buffer), totalItemsToConsume));
    }

    for (auto& th : producers) {
        th.join();
    }

    for (auto& th : consumers) {
        th.join();
    }

    return 0;
}
