#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;

/**
 * @brief 通过使用memory_order_release and memory_order_acquire and memory_order_acq_rel可以进一步规定
 * 不同线程间的原子操作的顺序，接下来通过三个线程描述这种同步关系：
 * release -> trigger acq_rel and acquire; acq_rel -> trigger acquire
 * @attention 我发现atomic 的store可以直接进行内存写入，但是读操作compare_exchange_strong or load都要在
 * 循环中进行读取，要有异常处理操作，可能会读取失败
*/

int main()
{
    vector<int> v;
    atomic<int> flag = {0};

    thread release([&](){
        v.push_back(42);
        flag.store(1, memory_order_release);
    });

    thread acqrel([&](){
        int expected = 1;
        while (!flag.compare_exchange_strong(expected, 2, memory_order_acq_rel))
        {
            cout << "compare and swap failded" << endl;
            // expected = 1;
        }
    });

    thread acquire([&](){
        int i = 0;
        while(flag.load(memory_order_acquire)<2) {
            cout << "wait " << ++i << " times" << endl;
        }
        cout << "v[0] = " << v.at(0) << endl;
    });

    release.join();
    acqrel.join();
    acquire.join();

    return 0;
}