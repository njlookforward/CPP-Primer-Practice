#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

int v = 1;
void critical_section(int change_v) {
    // mutex是static静态局部变量，这样多个线程才能竞争同一把锁
    static mutex mtx;
    unique_lock<mutex> lock(mtx);
    
    // 此时已经占据资源了，已经上锁了
    v = change_v;
    cout << "v = " << v << endl;

    // unique_lock解锁了，其他的unique_lock可以竞争锁资源
    lock.unlock();

    lock.lock();
    v += 1;
    cout << "v = " << v << endl;
}

int main()
{
    thread t1(critical_section, 2), t2(critical_section, 6);

    t1.join();
    t2.join();
    cout << "in the end, v = " << v << endl;

    return 0;
}