#include <iostream>
#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

int main()
{
    // 临界资源
    queue<int> produce_nums;
    bool notified = false;
    mutex mtx;
    condition_variable cv;

    // 生产者
    auto produce = [&](){
        for(int i = 0; ; ++i) {
            this_thread::sleep_for(chrono::milliseconds(900));
            unique_lock<mutex> lock(mtx);
            cout << "producing " << i << endl;
            produce_nums.push(i);
            notified = true;
            cv.notify_all();
        }
    };

    // 消费者
    auto consume = [&](){
        while(true) {
            unique_lock<mutex> lock(mtx);
            while (!notified)
            {
                cv.wait(lock);
            }

            lock.unlock();  // 让生产者再生产一会
            this_thread::sleep_for(chrono::milliseconds(1000));

            lock.lock();
            while (!produce_nums.empty())
            {
                cout << "consume " << produce_nums.front() << endl;
                produce_nums.pop();
            }
            notified = false;
        }
    };

    thread producer(produce);
    thread consumers[2];
    for(int i = 0; i < 2; ++i){
        consumers[i] = thread(consume);
    }
    producer.join();
    for (auto &t : consumers)
    {
        t.join();
    }
    return 0;
}