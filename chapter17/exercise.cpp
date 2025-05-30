#include "exercise.hpp"
using namespace std;

void initBookStoreSet(std::vector<std::vector<Sales_data>> &bookstores, std::ifstream &infile)
{
    vector<Sales_data> bookstore;
    Sales_data trans;
    while (infile >> trans)
    {
        bookstore.push_back(trans);
    }
    bookstores.push_back(bookstore);
}

matchSet_ptr findBook(std::vector<std::vector<Sales_data>> &bookstoreSet, const std::string &book)
{
    matchSet_ptr pset = make_shared<vector<matches>>();

    for(auto bgit_store = bookstoreSet.begin(); bgit_store != bookstoreSet.end(); ++bgit_store)
    {
        // 重载函数，只有到编译时才能知道，所以不要害怕报错
        stable_sort(bgit_store->begin(), bgit_store->end(), 
            static_cast<bool(*)(const Sales_data&, const Sales_data&)>(compareIsbn));
        // Bug: 在C++中，传入函数名作为函数指针的实参时，如果传入的是重载函数的函数名，且函数形参是一个模板类型
        // 并没有指出函数指针的类型，那么编译器是无法根据传入的函数名选择某个具体的函数版本，会发生歧义，因此需要使用
        // static_cast将函数实参显示转换成我们需要的函数指针类型，才能让编译器找到目标重载函数
        pair<vector<Sales_data>::iterator, vector<Sales_data>::iterator> scope = 
            equal_range(bgit_store->begin(), bgit_store->end(), Sales_data(book),
            static_cast<bool(*)(const Sales_data&, const  Sales_data&)>(compareIsbn));
        // Bug: 在标准库泛型算法equal_range中，搜索值类型必须与容器元素值类型保持一致，而且传入的比较算法应该比较的是
        // 两个相同类型的即容器元素类型的比较算法；因为他会交换容器元素类型的值与搜索值的顺序来实现>的算法，通过交换值的
        // 顺序使用一个<运算符同时实现</>/==的算法
        if(scope.first != scope.second)
            pset->push_back(make_tuple(bgit_store - bookstoreSet.begin(), 
                            scope.first, scope.second));
        else
            continue;
    }

    return pset;
}

void reportResults(std::istream &is, std::ostream &os, std::vector<std::vector<Sales_data>> &files)
{
    string book;
    while(true)
    {
        os << "Please input which book you want to realize sale data or q to quit: ";
        is >> book;
        if(!is || book == "q") break;
        auto pset = findBook(files, book);
        if(pset->empty()) {
            os << "Sorry, there isn't any data in the saleLibrary about " << book << endl;
            continue;
        } else {    
            for (const auto &item : *pset)
            {
                os << "store " << get<0>(item) << " sales: "
                     << accumulate(get<1>(item), get<2>(item), Sales_data(book)) << endl;
                     // Bug: 肯定有原因，accumulate是在<numeric>头文件中
            }
        }
    }
}

vector<std::pair<storeNo, found>> findBook_v2(std::vector<std::vector<Sales_data>> &bookStores, const std::string &book)
{
    // 自己想错了，答案说明需要用pair<size_type, pait<It, It>>来代替tuple<size_type, It, It>;
    // // 如果没有找到，就返回bookstores.size()和bgit_store.end()
    // for(auto bgit_store = bookStores.begin(); bgit_store != bookStores.end(); ++bgit_store)
    // {
    //     auto bookit = find_if(bgit_store->begin(), bgit_store->end(),
    //             [book](const Sales_data &item){ return item.isbn() == book; }); // Bug: find_if需要一元谓词
    //     if(bookit != bgit_store->cend())
    //         return make_pair(bgit_store - bookStores.cbegin(), bookit);
    // }
    // return make_pair(bookStores.size(), bookStores.begin()->end());
    vector<pair<storeNo, found>> matches;
    for(auto bgit_store = bookStores.begin(), edit_store = bookStores.end();
        bgit_store != edit_store; ++bgit_store)
    {
        sort(bgit_store->begin(), bgit_store->end(),
            static_cast<bool(*)(const Sales_data &, const Sales_data&)>(compareIsbn));
        auto found = equal_range(bgit_store->begin(), bgit_store->end(), Sales_data(book),
            static_cast<bool(*)(const Sales_data &, const Sales_data&)>(compareIsbn));
        
        if(found.first != found.second)
            matches.push_back({bgit_store - bookStores.begin(), found});
    }
    return matches;
}

pmatchset findBook_v3(std::vector<std::vector<Sales_data>> &bookstores, const std::string &book)
{
    pmatchset matchset = make_shared<vector<matchStore>>();

    for(auto bgit_store = bookstores.begin(); bgit_store != bookstores.end(); ++bgit_store)
    {
        stable_sort(bgit_store->begin(), bgit_store->end(),
            static_cast<bool(*)(const Sales_data&, const Sales_data&)>(compareIsbn));
        
        Sales_data tmp(book);
        auto found = equal_range(bgit_store->begin(), bgit_store->end(), tmp,
            static_cast<bool(*)(const Sales_data&, const Sales_data&)>(compareIsbn));
        if(found.first != found.second)
            matchset->push_back(matchStore(bgit_store - bookstores.begin(),
                                             found.first, found.second));
    }

    return matchset;
}

bool phoneValid(const std::smatch &phone)
{
    // 如果有左括号，那么必须有右括号，中间直接接数字或者空格
    if(phone[1].matched)
        return phone[3].matched &&
               (phone[4].matched == 0 || phone[4].str() == " ");
    
    // 如果没有左括号，那么也必须没有右括号，剩余两个连接符是一样的
    else
        return !phone[3].matched &&
               (phone[4].str() == phone[6].str());
}

void AddressBook(std::vector<peopleinfo> &phones, std::ifstream &infile)
{
    string format("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    regex re(format);

    string line;
    // Bug: 这么简单的逻辑我都会弄错，实在是不应该啊
    while (getline(infile, line))
    {
        istringstream iss(line);
        peopleinfo person;
        iss >> person._name;
        for(sregex_iterator bgit(line.begin(), line.end(), re), edit;
            bgit != edit; ++bgit)
        {
            person._phones.push_back(bgit->str());
        }
        phones.push_back(person);
    }
}

void printPhones(std::ostream &os, const std::vector<peopleinfo> &phones)
{
    string format("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    regex re(format);
    smatch result;

    for (const auto &entry : phones)
    {
        ostringstream formatted, badnums;
        for (const auto &phone : entry._phones)
        {
            if(regex_match(phone, result, re) && phoneValid(result))
            {
                formatted << " " << phone;
            } else
                badnums << " " << phone;
        }
        if(!formatted.str().empty())
            os << entry._name << formatted.str() << endl;
        if(!badnums.str().empty())
            os << "input error: " << entry._name 
               << " invalid number(s) " << badnums.str() << endl;
    }
}

std::vector<unsigned> good_randVec()
{
    // 必须保留状态，这样每次调用的时候是不一样的
    static default_random_engine e;
    static uniform_int_distribution<int> u(0, 9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 20; i++)
    {
        ret.push_back(u(e));
    }
    return ret;
}

unsigned int randomNum_v1()
{
    static default_random_engine e;
    static uniform_int_distribution<unsigned int> u(0, 9999);
    return u(e);
}

unsigned int randomNum_v2(long _seed)
{
    static default_random_engine e;
    static uniform_int_distribution<unsigned int> u(0, 9999);

    if(_seed >= 0)
        e.seed(_seed);
    return u(e);
}

unsigned int randomNum_v3(long _seed, long _min, long _max)
{
    // 必须是static的。可以记录状态
    static default_random_engine e;
    static uniform_int_distribution<unsigned int> u(0, 9999);

    if(_seed >= 0)
        e.seed(_seed);
    // 对于分布类型如果要指定范围的话，就不能使用static了
    // 我的想法是错的，尽管不能重新定义static对象，但是可以通过赋值的形式进行改变
    if(_max > _min)
        u = uniform_int_distribution<unsigned int>(_min, _max);

    return u(e);
}

bool play(bool first)
{
    static default_random_engine e;
    static bernoulli_distribution b;

    // 谁先置为1，谁就赢。
    bool mac, human;
    while(first)
    {
        mac = b(e);
        human = b(e);
        if(mac)
            return true;
        else if(human)
            return false;
        else
            continue;
    }
    while (!first)
    {
        mac = b(e);
        human = b(e);
        if(human)
            return false;
        else if(mac)
            return true;
        else
            continue;
    }
}

void word_tansform(std::ifstream &map_file, std::ifstream &text, std::ostream &os)
{
    auto transMap = buildMap(map_file);
    string line;
    while (getline(text, line))
    {
        istringstream iss(line);
        bool firstword = true;
        string word;
        while (iss >> word)
        {
            if(firstword)
                firstword = false;
            else
                os << " ";
            
            os << Tranform(word, transMap);
        }
        os << endl;
    } 
}

std::map<std::string, std::set<std::string>> buildMap(std::ifstream &map_file)
{
    map<string, set<string>> transMap;
    string _key, _val;
    while (map_file >> _key && getline(map_file, _val))
    {
        if(_val.size() > 1)
            transMap[_key].insert(_val.substr(1));  // 跳过空格
        else
            throw runtime_error("invalid value with " + _key);
    }
    return transMap;
}

const std::string &Tranform(const std::string &word, std::map<std::string, std::set<std::string>> &transMap)
{
    // 如何每次都不一样，应该使用time修改随机数发生器的种子
    // randomNum_v3(static_cast<long>(time(NULL)), 0, 9);
    // 是随机数引擎对象保存状态这样随机数才能指向序列中的下一个数，包括重新设置种子都是为了调整在随机数序列中的顺序
    // 随机数分布对象作用是确定分布类型，数据范围，数据类型
    // 引擎用来生成随机数，分布用来筛选随机数
    static default_random_engine e(static_cast<unsigned>(time(NULL)));
    if(transMap.count(word))
    {
        // 说明找到了有替换规则
        uniform_int_distribution<unsigned> u(0, transMap[word].size() - 1);
        auto bgit = transMap[word].begin();
        advance(bgit, u(e));
        return *bgit;
    } else
        return word;
}
