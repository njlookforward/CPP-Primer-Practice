#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <functional>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <algorithm>
#include "Shared_ptr.hpp"

// 对于设计泛型函数，应该使用统一的算法，对于compare来说，统一采用less进行比较，可以降低模版参数的要求
// 只要定义operator<运算符即可。而且通过使用std::less<T>可以跨平台运算，甚至可以比较指针类型
// 在模版定义中模版参数列表不能为空，关心类型无关和可移植性
template <typename T>
inline int compare(const T&v1, const T&v2)
{
    if(std::less<T>() (v1, v2)) return -1;  // 使用无名的less<T>函数对象进行比较，不要忘记()
    if(std::less<T>() (v2, v1)) return 1;

    return 0;
}

// 如果传入compare的是字符指针，则肯定匹配的是第一版本，但是他的算法逻辑是错的，因此需要进行函数模板特例化
// 必须带着template <> 说明是模板特例化
template <>
inline int compare(const char* const &v1, const char * const &v2)
{
    return strcmp(v1, v2);
}

// 我认为肯定会发生二义性，如果使用相同的名字的话
template <typename T, typename F = std::less<T>>
inline int compare_v2(const T&v1, const T& v2, F f = F())
{
    if(f(v1, v2)) return -1;
    if(f(v2, v1)) return 1;
    return 0;
}

// 在模版中，有模版类型参数和模版非类型参数
// 类型参数可以用在函数的返回值类型，形参类型，函数体内用于变量的声明和类型转换
// template <class T> T Foo(T *p)
// {
//     T tmp = *p;
//     return tmp;
// }
// 类型参数可以使用关键字typename and class
// template <typename T, class U>
// void calc(const T&, const U&);

// 非类型参数可以是整数，或者指向静态对象或者函数的指针或者左值引用，必须用常量表达式进行赋值
// 因为这样编译器才能在编译阶段实例化模版
template <size_t N, size_t M>
int compare(const char (&a1)[N], const char (&a2)[M])
{
    // 字符数组没有operator<，因此仍然需要使用strcmp
    // 说明字符数组类型实参传递给函数时，自动转换为const char*，这是精确匹配
    return strcmp(a1, a2);
}

// inline and constexpr的正确位置
// template <typename T> inline constexpr T min(const T&, const T&) {}

// exercise_16_4
template <typename Iterator, typename T>
inline Iterator Find(Iterator first, Iterator last, T val)
{
    Iterator iter = first;
    while (iter != last)
    {
        if(*iter == val)
            return iter;
        else
            ++iter;    
    }
    return iter;
}

template <typename Iterator, typename Pred>
inline Iterator Find_if(Iterator first, Iterator last, Pred pred)
{
    // Bug3: 竟然没有给iter赋值，又犯马虎了
    Iterator iter = first;
    while (iter != last)
    {
        if(pred(*iter))
            return iter;
        else
            ++iter;    
    }
    return iter;
}

// Bug: 出现链接错误，凡是定义在头文件中的函数，必须定义为inline，否则的话会出现重定义问题，而函数模板是默认inline函数的
inline void checkArgs(int argc, int thresh)
{
    if(argc != thresh)
        throw std::runtime_error("Input arguments mount is invalid");
}

inline void OpenInputFile(std::ifstream &infile, const std::string &dir)
{
    infile.open(dir);
    if(!infile)
    {
        std::cerr << "Sorry, cannot open " << dir << std::endl;
        std::exit(-1);
        // Bug4：又是逻辑问题，竟然把exit单独放在if的外面，这不是永远结束进程吗，可恶啊，这种失误浪费了太多的时间
    }
}

template <typename Container>
void ReadIntoContainer(std::istream &is, Container &con)
{
    typename Container::value_type val;
    while (is >> val)
    {    
        con.insert(con.end(), val);    
    }

    if(!is.eof() && is.fail())
        throw std::runtime_error("ReadIntoContainer(istream &, Container &): input occurs error");
    // 当达到文件流末尾时，会同时置位eof和fail
    // 但是如果发生问题，只会置位fail或bad, 而且发生不可改变的错误会同时置位fail和bad
}

// 需要针对const char*进行特例化，只要进行了特例化，这个就是一个实际的函数了，定义在头文件中必须使用inline
template <>
inline void ReadIntoContainer(std::istream &is, std::vector<char*> &vec)
{
    std::string str;
    while (is >> str)
    {
        // 为什么要使用new char[]呢？对象在多个函数之间进行传递时，能够使用的共享的共同访问的就是指针
        // 就是堆空间，因此要使用new，返回到调用点后，vec中保存的指针仍然是有效的
        auto p = new char[10];
        strcpy(p, str.c_str());
        vec.push_back(p);
    }
    if(!is.eof() && is.fail())
        throw std::runtime_error("ReadIntoContainer(istream&, vector<const char*>): input occurs error");
}

inline void freeVec(std::vector<char*> &vec)
{
    for(auto &p : vec)
        delete [] p;
}

// 练习尝试一下部分实例化函数模板，而且改变的不是模板参数数目，而是模板参数类型
// 想错了，这个不是函数模板特例化，而是函数模板重载
template <typename T, std::size_t N>
void ReadIntoContainer(std::istream &is, T (&arr)[N])
{
    T value;
    for(std::size_t i = 0; i < N && is >> value; ++i)
    {
        arr[i] = value;
    }
    // 只有到达文件流末尾的输入错误才可以接受
    if(!is.eof() && is.fail())
        throw std::runtime_error("ReadIntoContanier(istream &, T(&)[N]): input occurs error");
}

// exercise_16_5
template <std::size_t N, typename T>
void print(const T (&arr)[N])
{
    for (const auto &val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// exercise_16_6
// 定义自己版本的数组参数的begin和end函数，先不要想太多，先完成一个功能再说
// 对于数组来说，一旦确定N，就一定会分配这么多的元素，因此目前的问题就是N=0会怎么样，应该不可能吧
template <typename T, std::size_t N>
T *Begin(T (&arr)[N])
{
    return &arr[0];
}

template <typename T, std::size_t N>
T *End(T (&arr)[N])
{
    return &arr[N];
}

// exercise_16_7
template <typename T, std::size_t N>
constexpr std::size_t Size(T (&arr)[N])
{
    return N;
}

// 练习通用和特定的模板友好关系
// 定义非模板类与模板类的特例的友元关系
template <typename> class Pal;
class C {
    friend class Pal<C>;    // 与特例的友元关系
    template <typename> friend class Pal2;   // 与所有的Pal2的特例都建立友元
};

template <typename T>
class C2 {
    friend class Pal<T>;
    template <typename X> friend class Pal2; // 与所有的Pal2的特例建立友元
    friend class Pal3;
};

// 新标准允许我们为模板定义别名
// Bug6:模板函数的定义必须放在头文件中，包括定义类模板的类型别名也要放在头文件中
template <typename T> using Twin = std::pair<T, T>;  // 其实隐式地指出Twin<T>=pair<T,T>;
// 当我们定一个模板类型别名时，可以固定一个或多个模板参数
template <typename T> using partNo = std::pair<T, unsigned>;
// Bug7: template <typename> class C，这是模板；但是一旦定义template <typename> class C<T>这就不是模板了，
// 只要一加上<T>就是一个类类型，因此模板与类类型要分清楚                           

// 定义类模板的static成员
template <typename T>
class Foo {
public:
    static std::size_t count() {    return _ctr;    }

private:
    static std::size_t _ctr;
};

template <typename T>
std::size_t Foo<T>::_ctr = 0;   // 需要按照类模板成员函数的方式进行定义

template <typename Container>
inline void display(std::ostream &os, const Container &con)
{
    for (const auto &val : con)
    {
        os << val << " ";
    }
    os << std::endl;
}

template <typename Container>
inline void display_v2(const Container &c)
{
    for(typename Container::size_type i = 0; i < c.size(); ++i)
        std::cout << c.at(i) << " ";    // 对于顺序容器中的可以随机访问的容器，应该使用at返回元素
    std::cout << std::endl;
}

template <typename Container>
inline void display_v3(const Container &c)
{
    for(typename Container::const_iterator bgit = c.cbegin();
        bgit != c.cend(); ++bgit)
        std::cout << *bgit << " ";
    std::cout << std::endl;
}

template <typename T>
inline typename T::value_type top(const T &C)
{
    if(!C.empty())
        return C.back();    // 返回的是最后一个元素
    else
        return typename T::value_type();    // 容器类型的值初始化
}

template <typename T = int> class Numbers {
public:
    Numbers(T v): _val(v) {}
private:
    T _val;
};

// 成员模板，不管是非模板类还是模板类都可以定义各自的模板成员函数，简称成员模板
class DebugDelete {
public:
    DebugDelete(std::ostream &os = std::cerr): _os(os) {}

    template <typename T>
    void operator()(T *p) const
    {
        _os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &_os;
};

template <typename T> T fobj(T t1, T t2) {  return t1 < t2 ? t1 : t2;}
template <typename T> T fref(const T&t1, const T&t2) {  return t1 < t2 ? t1 : t2;   }

// 使用尾置返回类型
template <typename It>
auto fcn(It bgit, It edit) -> decltype(*bgit)
{
    return *bgit;
}

// 为了进行类型转换，得到引用的元素类型
template <typename It>
auto fcn2(It bgit, It edit) ->
    typename std::remove_reference<decltype(*bgit)>::type
{
    return *bgit;
}

// exercise_16_41 不知道什么意思，应该是加法
template <typename T1, typename T2>
auto sum(T1 a, T2 b) -> decltype(a + b)
{
    return a + b;
}

inline void func(int (*)(const int&, const int&)) {}
inline void func(int (*)(const std::string&, const std::string&)) {}

// 定义自己的std::move
template <typename T>
typename std::remove_reference<T>::type&& myMove(T&& val)
{
    return static_cast<typename std::remove_reference<T>::type&&>(val);
}

// 定义自己的std::forward
template <typename T>
inline T&& myForward(typename std::remove_reference<T>::type& val)
{
    return static_cast<T&&>(val);   // 真是巧妙啊，利用引用折叠得到T的真正的值类别
}

// 利用函数模板的部分特例化实现自己的std::remove_reference<T>的实现
// Bug: 不应该使用class，而是使用struct，否则type是无法被使用的
template <typename T>
struct my_remove_reference {
    typedef T type;
};

// 函数模板部分特例化
template <typename T>
struct my_remove_reference<T&> {
    typedef T type;
};

template <typename T>
struct my_remove_reference<T&&> {
    typedef T type;
};

// 模板参数转发，要使用右值引用和std::forward<T>保持传入参数的类型，还有值类别
template <typename F, typename T1, typename T2>
inline void flip(F f, T1 &&t1, T2&& t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

inline void f(int v1, int& v2)
{
    std::cout << v1 << " " << ++v2 << std::endl;
}

inline void g(int &&v1, int &v2)
{
    std::cout << v1 << " " << v2 << std::endl;
}

/*******重载与模板*******/
template <typename T> std::string debug_rep(const T& t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

// 模板重载函数，编译器会匹配最特例化的版本
template <typename T> std::string debug_rep(T *p)
{
    std::ostringstream oss;
    oss << "pointer: " << p;   // 注意p的指针类型不能是char*，否则会输出字符串的
    if(p)
        oss << " " << debug_rep(*p);
    else
        oss << " nullptr";
    return oss.str();
}

// ########非模板重载函数
// inline std::string debug_rep(const std::string &str)
// {
//     return "\"" + str + "\""; 
// }

// inline std::string debug_rep(char *p)
// {
//     return debug_rep(std::string(p));
// }

// inline std::string debug_rep(const char *p)
// {
//     return debug_rep(std::string(p));
// }

// exercise_16_65
// #######使用函数模板特例化##代替非模板重载函数
template <> 
inline std::string debug_rep(const std::string &s)
{
    return "\"" + s + "\"";
}

// 注意，为什么要进行函数模板特例化或者类模板特例化，因为该模板参数类型不适用于通用的逻辑
// 要单独为某个模板实参定义特定的逻辑处理，因此进行特例化
template <>
inline std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

template <>
inline std::string debug_rep(const char* cp)
{
    return debug_rep(std::string(cp));
}

/******可变参数模板******/
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest)
{
    std::cout << "template parameter packet: " << sizeof...(Args) << std::endl
              << "function parameter packet: " << sizeof...(rest) << std::endl;
}

// 可变参数函数通常是递归的
// 非可变参数模板比可变参数模板更加特例化
template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    return os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args& ... rest)
{
    // 为什么要有t，而不是全部都是rest呢，因为rest不是具体的形参，他是一个函数参数包，除了包扩展之外，没有多少操作空间
    // 因此必须有一个额外的t，用来在递归中将参数包中的一个参数剥离出来
    os << t << ", ";
    return print(os, rest ...); // 大胆尝试这种写法
}

// 理解包扩展, 把模板/函数参数包当做一个参数进行使用，然后不要忘记...
template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args& ... args)
{
    return print(os, debug_rep(args) ...);
}

// exercise_16_61
template <typename T, class... Args>
Shared_ptr<T> my_make_shared(Args&&... args)
{
    return Shared_ptr<T>(new T(std::forward<Args>(args)...));
}


// exercise_16_63
template <typename T>
inline std::size_t countOccur(const std::vector<T> &vec, const T &val)
{
    auto bgit = vec.cbegin(),
         edit = vec.cend();
    std::size_t cnt = 0;
    for(; (bgit = find(bgit, edit, val)) != edit; ++bgit)
        ++cnt;
    
    return cnt;
}

// exercise_16_64 函数模板特例化
// 为什么要对const char*单独进行特例化，因为按照通用函数模板的逻辑，两者比较的指针，而且没有使用equal<const char*>
// 是无法比较两个指针的，比较两个字符指针的值，必须使用strcmp，不需要去管const char*的指针到底指向哪，只需要管值就好
template <>
inline std::size_t countOccur(const std::vector<char*> &vec, char* const &val)
{
    auto bgit = vec.cbegin(),
         edit = vec.cend();
    std::size_t cnt = 0;
    // Bug: 真正的错误是strcmp(), 它的结果取决于差值，若相等的话，返回的是0
    for(; (bgit = find_if(bgit, edit, [val](char *elem) { return !strcmp(elem, val);  }))
            != edit; ++bgit)
        ++cnt;
    return cnt;
    // std::size_t cnt = 0;
    // for (auto p : vec)
    // {
    //     if(!strcmp(p, val))
    //         ++cnt;
    // }
    // return cnt;
}

template <typename T>
T f1(T t1, T t2)
{
    if(std::less<T>()(t1, t2)) return t1;
    else return t2;
}

#endif