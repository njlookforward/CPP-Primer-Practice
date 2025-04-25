#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

/**
 * @brief 对于临界区的访问要使用互斥量mutex对象，采用RAII机制的写法进行临界区的加锁和解锁
*/

int v = 1;
void critical_section(int change_v) {
    static mutex mtx;
    {
        lock_guard<mutex> lock(mtx);
        v = change_v;
        cout << "v = " << v << endl;
    }
}

int main()
{
    thread t1(critical_section, 2),
           t2(critical_section, 3);
    
    t1.join();
    t2.join();

    cout << "in the end, v = " << v << endl;
    return 0;
}