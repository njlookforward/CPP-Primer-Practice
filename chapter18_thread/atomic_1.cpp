#include <thread>
using std::thread;

#include <iostream>
using std::cout; using std::endl;

int main() {
    int a = 0;
    volatile int flag = 0;

    thread t1([&]() {
        while (flag != 1);

        int b = a;
        cout << "b = " << b << endl;
    });

    thread t2([&](){
        a = 5;
        flag = 1;
        cout << "thread2 a = " << a << "\t flag = " << flag << endl;
    });

    t1.join();
    t2.join();
    return 0;
}