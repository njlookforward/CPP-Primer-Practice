#include <atomic>
#include <thread>
#include <iostream>
using namespace std;

/**
 * @brief 释放/消费模型：我认为通过使用一对memory_order_release and memory_order_consume规定了两个或多个线程之间的同步顺序
 * memory_order_release之前的内存写入操作在完成memory_order_release之后对其他线程都是可见的，而其他线程中来到
 * memory_order_consume会等待某一个线程中的memory_order_release完成操作，实现同步，因此memory_order_consume之后的
 * 操作都可见其他线程的内存写入操作，
 * key0: 确保memory_order_consume的原子操作一定在memory_order_release原子操作之后进行操作
 * key1: 无论是叫因果一致性，线性一致性，最终一致性，内存顺序都OK，本质上都是同步问题，类似于加上互斥锁，不要被各种新名词误导
 * key2: 通过使用memory_order_*确定不同线程间原子操作的顺序
*/

int main()
{
    // 这些都是全局变量
    atomic<int *> ptr = nullptr;
    int v = 0;

    thread producer([&](){
        int *p = new int(42);
        v = 1024;
        ptr.store(p, memory_order_release);
    });

    thread consumer([&](){
        int *p;
        while(!(p = ptr.load(memory_order_consume)));
        // p = ptr.load(memory_order_consume);

        cout << "*p = " << *p << endl;
        cout << "v = " << v << endl;
    });

    producer.join();
    consumer.join();
    int *p = ptr.load();
    if(p) {
        cout << "*p exist: " << *p << endl;
        delete p;
    }
    
    return 0;
}