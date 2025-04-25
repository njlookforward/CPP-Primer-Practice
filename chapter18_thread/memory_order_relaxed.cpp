#include <atomic>
using std::atomic;

#include <thread>
using std::thread;

#include <vector>
using std::vector;

#include <iostream>
using std::cout; using std::endl;

/**
 * @brief memory_order_relaxed宽松模型，单个线程内的原子操作都是顺序进行的，不允许指令重排，但是多个线程
 * 间的原子操作的顺序是任意的
 * @attention 我认为使用memory_order_relaxed，同步的临界区仅限于原子对象，对于其他的全局变量，其实也是临界区
 * 的内存顺序没有规定，相当于仅仅对原子对象加锁
*/

int main()
{
    vector<thread> vt;  // 线程池
    atomic<int> counter = {0};

    for(int i = 0; i < 100; ++i) {
        vt.emplace_back([&](){
            counter.fetch_add(1, std::memory_order_relaxed);
            cout << "thread " << i+1 << ": counter = " << counter << endl;
        });
    }

    for (auto &t : vt)
    {
        t.join();
    }

    cout << "in the end, counter = " << counter << endl;

    return 0;
}