#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;

/**
 * @brief 顺序一致模型：原子操作满足顺序一致性，是不是更严格的同步操作，对性能会产生损耗
*/

int main()
{
    atomic<int> counter = {0};
    vector<thread> vt;
    for(int i = 0; i < 100; ++i) {
        vt.emplace_back([&](){
            counter.fetch_add(1, memory_order_seq_cst);
            // cout << "thread " << i+1 << " counter = " << counter.load() << endl;
        });
    }
    for (auto &t : vt)
    {
        t.join();
    }
    cout << "in the end, counter = " << counter.load() << endl;
    return 0;
}