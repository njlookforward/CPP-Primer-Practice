#include <future>
#include <thread>
#include <iostream>
using namespace std;

/**
 * @brief by future get异步操作的结果
*/

int main()
{
    packaged_task<int()> task([](){return 7;});
    future<int> result = task.get_future(); // 此时已经拉起来一个任务线程
    thread(move(task)).detach();
    cout << "waiting... ";
    result.wait();  // 等待的屏障
    
    cout << "done!" << endl
         << "result = " << result.get() << endl;

    return 0;
}