#include <thread>
#include <iostream>
using namespace std;

int main()
{
    // thread是并发编程的基础
    thread t([](){
        cout << "Hello, concurrency world!" << endl;
    });

    cout << "thread id: " << t.get_id() << endl;
    t.join();   // 等待该线程结束，与主线程汇合

    return 0;
}