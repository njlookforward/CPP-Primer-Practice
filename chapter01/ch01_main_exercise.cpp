#include "Sales_item.hpp"
#include <fstream>

void exercise_1_20()
{
    Sales_item book;

    while (std::cin >> book)
    {
        std::cout << book << std::endl;
    }
}

void exercise_1_22()
{
    // 读取多个具有相同ISBN的销售记录，输出和
    Sales_item totalBook;
    if (std::cin >> totalBook)
    {
        Sales_item tmpBook;
        while (std::cin >> tmpBook)
        {
            if(checkCompare(totalBook, tmpBook))
                totalBook += tmpBook;
            else
            {
                std::cout << totalBook << std::endl;
                totalBook = tmpBook;
            }    
        }
        std::cout << totalBook << std::endl;
    }
    else
        std::cerr << "Please input Sales_item in right formulation." << std::endl;
}

void exercise_1_23()
{
    int soldcount = 1;
    Sales_item aimBook, comBook;
    std::cin >> aimBook;
    while (std::cin >> comBook)
    {
        if(checkCompare(aimBook, comBook))
            ++soldcount;
        else
        {
            std::cout << aimBook.isbn() << " sold " << soldcount << " times." << std::endl;
            aimBook = comBook;
            soldcount = 1;
        }
    }
    std::cout << aimBook.isbn() << " sold " << soldcount << " times." << std::endl;
}

void exercise_1_3()
{
    std::cout << "Hello, World." << std::endl;
}

void exercise_1_4()
{
    std::cout << "Enter two numbers: ";
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The multiplication of " << v1 << " and " << v2
              << " is " << v1 * v2 << std::endl;
}

void exercise_1_6()
{
    /* 程序不合法，因为第一行和第二行结尾有分号，分号说明这条statement结束了，就无法连续输出
     * 应该去掉分号
     */
}

void exercise_1_7()
{
    /*
     * 注释对不能嵌套。
     * “不能嵌套”几个字会被认为是源码
     * 像剩余程序一样进行处理
     * 因此若需要注释掉某些代码时，用单行注释//不会出现问题
     */
}

void exercise_1_8()
{
    // std::cout << "/*";
    // std::cout << "*/";
    // std::cout << /* "*/" */;
    std::cout << /* "*/" /* "/*" */;
}

void exercise_1_9()
{
    int sum = 0, val = 50;
    while (val <= 100)
    {
        sum += val;
        ++val;
    }
    std::cout << "Sum of 50 to 100 inclusive is "
              << sum << std::endl;
}

void exercise_1_10()
{
    int val = 10;
    while (val >= 0)
    {
        std::cout << val << " ";
        --val;
    }
    std::cout << std::endl;
}

void exercise_1_11()
{
    std::cout << "Please enter two integer: ";
    int first, last;
    std::cin >> first >> last;
    while (first <= last)
    {
        std::cout << first << " ";
        ++first;
    }
    std::cout << std::endl;
}

void exercise_1_13()
{
    int sum = 0;
    for(int val = 50; val <= 100; ++val)
        sum += val;
    std::cout << "For sum of 50 to 100 inclusive is " << sum
              << std::endl;
    
    for(int val = 10; val >= 0; --val)
        std::cout << val << " ";
    std::cout << std::endl;

    int first, last;
    std::cout << "Please enter two numbers to print [first, last] numbers: ";
    std::cin >> first >> last;
    for ( ; first <= last; ++first)
    {
        std::cout << first << " ";
    }
    std::cout << std::endl; 
}

void exercise_1_14()
{
    // for循环省去了++或--的环节
}

void exercise_1_15()
{
    std::cout << "Read each file." << std::endl;
    std::cout << "Update master." << std::endl;
    std::cout << "Write new master." << std::endl;

    int v1, v2;
    std::cin >> v1 >> v2;
    std::cout << v1+v2 << std::endl;
}

void exercise_1_19()
{
    std::cout << "Please enter two integer: ";
    int first, last;
    std::cin >> first >> last;
    if(first < last)
    {
        while (first <= last)
        {
            std::cout << first << " ";
            ++first;
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Sorry, please first number must less than second number" << std::endl;
    }
}

int main()
{
    // exercise_1_3();
    // exercise_1_4();
    // exercise_1_7();
    // exercise_1_8();
    // exercise_1_9();
    // exercise_1_10();
    // exercise_1_11();
    // exercise_1_13();
    // exercise_1_15();
    // exercise_1_19();
    // exercise_1_20();
    // exercise_1_22();
    // exercise_1_23();

    return 0;
}