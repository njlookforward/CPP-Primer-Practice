#include "exercise.hpp"

void prog1_map_set(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    map<string, size_t> word_count;
    set<string> exclude{"The", "But", "And", "Or", "An", "A",
                        "the", "but", "and", "or", "an", "a"};
    string word;
    while (infile >> word)
    {
        if(exclude.find(word) == exclude.end())
            ++word_count[word];
    }
    // for (const auto &w : word_count)
    // {
    //     cout << w.first << " occurs " << w.second
    //          << (w.second > 1 ? " times." : " time.") << endl;
    // }
    for(auto iter = word_count.cbegin(); iter != word_count.cend(); ++iter)
        cout << iter->first << " occurs " << iter->second << " times." << endl;

    auto mapiter = word_count.begin();
    // mapiter->first = string("new type"); 
    ++mapiter->second;
    cout << mapiter->first << " has " << mapiter->second << endl;

    infile.close();
}

void prog2_map_set()
{
    map<string, string> authors = { {"Joyce", "James"},
                                    {"Austen", "Jane"},
                                    {"Dickens", "Charles"}};

    vector<int> ivec;
    for (int i = 0; i < 10; i++)
    {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    
    // set中的关键字是唯一的，不能重复
    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> miset(ivec.cbegin(), ivec.cend());

    cout << "ivec's size is " << ivec.size() << endl
         << "iset's size is " << iset.size() << endl
         << "miset's size is " << miset.size() << endl;
}

void prog3_key(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    // map/multimap/set/multiset 关键字要提供operator<或者自定义比较操作
    // multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
    // exercise_11_11
    set<Sales_data, bool (*) (const Sales_data &, const Sales_data &)>  // 为什么要使用函数指针而不是函数作为形参类型呢？因为函数无法拷贝，只有通过函数指针才能够进行拷贝操作，和数组是一个道理
        bookstore([] (const Sales_data &lhs, const Sales_data &rhs)
                            {   return lhs.isbn() < rhs.isbn(); });
    // 通过这个set的自定义，可以看出自己的模板编程的能力还差得很远很远，这是能够看懂，用都费劲，更别说自己定义一个模板算法了
    Sales_data trans;
    while (infile >> trans)
    {
        bookstore.insert(trans);
    }
    // display(cout, bookstore);

    // exercise_11_19
    typedef bool (*pf) (const Sales_data &, const Sales_data &);
    set<Sales_data, pf>::iterator bgit = bookstore.begin();
    auto endit = bookstore.end();
    while (bgit != endit)
    {
        cout << *bgit++ << endl << endl;
    }

    infile.close();
}

void prog4_pair()
{
    pair<string, string> author{"James", "Joyce"};
    pair<string, size_t> word_count("data", 3);
    pair<string, vector<int>> line = {"example", {1, 3, 8}};
    cout << word_count.first << " occurs " << word_count.second << " times." << endl; 

    // associative container's type
    set<string>::key_type v1;
    set<string>::value_type v2;
    map<string, int>::key_type v3;
    map<string, int>::mapped_type v4;
    map<string, int>::value_type v5;

    // set's iterator is const
    set<int> iset{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto set_it = iset.cbegin();
    while (set_it != iset.end())
    {
        // *set_it *= 2;    // set's iterator is only iterator, don't have const_iterator, but it is const
        cout << *set_it++ << " ";
    }
    cout << endl;
}

void prog5_insert(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    vector<int> ivec{2, 4, 6, 8, 2, 4, 6, 8};
    set<int> iset;
    iset.insert(ivec.begin(), ivec.end());
    iset.insert({1, 3, 5, 7, 1, 3, 5, 7});
    display(cout, iset);

    map<string, size_t> word_count;
    // word_count.insert({"lippman", 2});
    // word_count.insert(make_pair("smith", 3));
    // word_count.emplace("mailer", 2);
    // word_count.insert(pair<string, size_t>("franz", 1));
    // word_count.insert(map<string, size_t>::value_type("orlen", 4));
    // word_count.emplace("ranier", 3);
    // print(word_count);

    string name; int cnt;
    while (infile >> name >> cnt)
    {
        // cnt = 1;
        pair<map<string, size_t>::iterator, bool> ret = word_count.insert(make_pair(name, cnt));
        if(!ret.second)
            // ++ret.first->second;
            ret.first->second = cnt;
    }
    auto &nameCnt = word_count.at("lippman");
    nameCnt += 10;
    print(word_count);
    // word_count.at("nanjiang");   // throw an exception called out_of_rage
    // 若想单纯的查询关键字，而不需要讲不在容器中的关键字插入到容器中，使用find
    if(word_count.find("foobar") == word_count.end())
        cout << "foobar is not in the map." << endl;

    multimap<string, string> authors;
    // ERROR！！！！！！ Never forget to insert a pair, need to use {}
    authors.insert({"Barth, John", "Sot-Weed Factor"});
    authors.insert({"Barth, John", "Lost in the Funhouse"});
    print(authors);

    auto delcnt = authors.erase("Barth, John");
    cout << delcnt << " elements are deleted." << endl;

    infile.close();
}

void prog6_access()
{
    // 注意在关联容器中访问或者称之为查找元素，使用的是关键字进行查询
    set<int> iset{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = iset.find(1);
    if(iter != iset.end())
        cout << *iter << endl;
    
    iter = iset.find(11);
    if(iter == iset.end())
        cout << "No found." << endl;
    
    auto cnt = iset.count(1);
    cout << cnt << endl;
    cnt = iset.count(11);
    cout << cnt << endl;
}

void prog7_text_convert(int argc, char *argv[])
{
    checkargc(argc, 3);
    ifstream rulesFile, textFile;
    openinfile(rulesFile, argv[1]);
    openinfile(textFile, argv[2]);
    
    if(argc == 4)
    {
        ofstream outfile;
        openoutfile(outfile, argv[3]);
        textConvert(rulesFile, textFile, outfile);
        outfile.close();
    }
    else
        textConvert(rulesFile, textFile);
    
    rulesFile.close();
    textFile.close();
}

void prog8_unordered_map_set(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    unordered_map<string, size_t> word_count;
    string word;
    while (infile >> word)
    {
        ++word_count[word];
    }
    for (const auto &entry : word_count)
    {
        cout << entry.first << " occurs " << entry.second
             << (entry.second > 1 ? " times." : " time.") << endl;
    }

    infile.close();
}

void prog9_class_unorder(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    // unordered_multiset<Sales_data, decltype(hasher) *> soldMsg(42, hasher);
    unordered_set<Sales_data, decltype(hasher)*> soldMsg(42, hasher);
    Sales_data trans;
    while (infile >> trans)
    {
        soldMsg.insert(trans);
    }
    display(cout, soldMsg);

    infile.close();
}

int main(int argc, char **argv)
{
    prog1_map_set(argc, argv);
    // prog2_map_set();
    // prog3_key(argc, argv);
    // prog4_pair();
    // prog5_insert(argc, argv);
    // prog6_access();
    // prog7_text_convert(argc, argv);
    // prog8_unordered_map_set(argc, argv);
    // prog9_class_unorder(argc, argv);

    return 0;
}

// 哪怕只有一秒钟，一分钟，一小时也是一种重大胜利，不要在乎时长，不要磨洋工，认认真真过好当下的每一秒钟
// 一道题一道题的练，一个字一个字地看，一行行地看，一步一步地走，走得坚实而有力量，拿出你的激情
// 很多东西没见过，多见多练就好了，不要怕，拿出就做出一堆狗屎的心态行动就好了
// 读出声来，大声地说出自己的思路，爷就是自信，有耐心，不着急，不要掉进时间的陷阱里
// 不想干的时候，划线粗读就行了，或者一道一道地练代码，丢掉所有包袱，享受当下