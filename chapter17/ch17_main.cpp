#include <tuple>
#include <cstddef>
#include <string>
#include <vector>
#include <list>

using namespace std;

void prog1_tuple()
{
    tuple<size_t, size_t, size_t> threeD;   // 默认构造函数进行值初始化，都为0
    tuple<string, vector<double>, int, list<int>>
        someVal("consntants", {3.14, 2.718}, 42, {0,1,2,3,4,5});
}

int main(int argc, char **argv)
{
    prog1_tuple();

    return 0;
}