#include "Sales_item.hpp"
#include <fstream>
#include <cstdlib>

void prog1_sales_item()
{
    std::ofstream logfile("loginfo.txt", std::ios::app);
    if(!logfile)
    {
        std::cerr << "Oops, cannot open loginfo.txt.\n";
        exit(0);
    }

    Sales_item book_1,
               book_2(std::string("978-7-121-15535-2"));

    logfile << "default constructor:\t" << book_1
            << "string constructor:\t" <<book_2 << std::endl;
    
    std::cin >> book_1;
    logfile << "after input into book1:\t" << book_1;

    book_2.soldCount(1300);
    book_2.totalRevenue(128.00);
    Sales_item book_3(book_1);
    if(book_2.isbn() != book_3.isbn())
    {
        book_3.isbn(book_2.isbn());
    }
    book_3 = book_3 + book_2;
    logfile << book_2 << "after 2+3:\n"
            << book_3;
}

void prog2_sales_item()
{
    // Sales_item book;
    // std::cin >> book;
    // std::cout << book << std::endl;

    Sales_item item1, item2;
    std::cin >> item1 >> item2;
    if (item1.isbn() == item2.isbn())
    {
        std::cout << item1 + item2 << std::endl;
    } else {
        std::cerr << "Data must refer to same isbn" << std::endl;
    }
}

void prog3_iostream()
{
    std::cout << "Enter two numbers: ";
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The sum of " << v1 << " and " << v2
              << " is " << v1 + v2 << std::endl;
}

void prog4_while()
{
    int sum = 0, val = 1;
    while (val <= 10)
    {
        sum += val;
        ++val;
    }
    std::cout << "Sum of 1 to 10 inclusive is "
              << sum << std::endl;
}

void prog5_for()
{
    int sum = 0;
    for(int val=1; val <= 10; ++val)
        sum += val;
    std::cout << "for Sum of 1 to 10 is " << sum
              << std::endl;
}

void prog6_cin()
{
    int sum = 0, value;
    while (std::cin >> value)
    {
        sum += value;
    }
    std::cout << "Sum is " << sum << std::endl;
}

void prog7_if()
{
    int curVal, val;
    if(std::cin >> curVal)
    {
        int cnt = 1;
        while (std::cin >> val)
        {
            if(curVal == val)
                ++cnt;
            else
            {
                std::cout << curVal << " occurs " << cnt << " times" << std::endl;
                curVal = val;
                cnt = 1;
            }    
        }
        std::cout << curVal << " occurs " << cnt << " times" << std::endl;
    }
}

int main()
{
    // prog1_sales_item();
    // prog2_sales_item();
    // prog3_iostream();
    // prog4_while();
    // prog5_for();
    // prog6_cin();
    prog7_if();

    return 0;
}