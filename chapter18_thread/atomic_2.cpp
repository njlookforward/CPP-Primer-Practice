#include <atomic>
using std::atomic;

#include <thread>
using std::thread;

#include <iostream>
using std::cout; using std::endl;

atomic<int> count(0);

int main()
{
    thread t1([](){
        count.fetch_add(1);
        cout << "thread1 count = " << count << endl;
    });

    thread t2([](){
        count++;
        cout << "thread2 count = " << count << endl;
    });

    thread t3([](){
        count += 1;
        cout << "thread3 count = " << count << endl;
    });

    t1.join();
    t2.join();
    t3.join();

    cout << "count = " << count << endl;
    return 0;
}