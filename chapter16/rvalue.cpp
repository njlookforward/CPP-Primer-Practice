#include <iostream>
#include <type_traits>

int g = 42;

int& get_left() { return g; }    // 返回左值引用
int&& get_right() { return 42; } // 返回右值引用（危险操作，仅用于演示）

int main() {
    // 检查值类别
    static_assert(std::is_lvalue_reference<decltype(get_left())>::value, "lvalue");
    static_assert(std::is_rvalue_reference<decltype(get_right())>::value, "rvalue");

    // 验证可操作性
    get_left() = 100;                   // ✔️ 左值可修改
    // int* p = &get_right();           // ❌ 编译错误：右值不能取地址

    std::cout << g << std::endl;        // 输出 100
}