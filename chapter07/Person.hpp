#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>

// exercise_7_4     exercise_7_5
struct Person {
    friend std::istream &read(std::istream &is, Person &per);
    // friend std::ostream &print(std::ostream &os, const Person &per);

public:
    // exercise_7_15
    Person() = default;
    Person(const std::string &name, const std::string &addr);
    // exercise_7_50
    // 只有含有一个参数的构造函数才会成为转换构造函数，而且我认为是不是explict无所谓

    // 这两个函数需要声明并定义成const成员函数，因为只需要读取数据成员，不需要进行改变
    const std::string &name() const     {   return _name;   }
    const std::string &address() const  {   return _address;    }

private:
    std::string _name;      // 人员姓名
    std::string _address;   // 人员住址
};

// exercise_7_9
std::istream &read(std::istream &is, Person &per);
std::ostream &print(std::ostream &os, const Person &per);

class Y;    // forward declaration
class X {
private:
    Y *_py;
};

class Y {
private:
    X _objx;
};

#endif  // PERSON_HPP