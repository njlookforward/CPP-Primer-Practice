#include "exercise.hpp"

// exercise_11_1
// map是关联容器，容器中存储的元素是键值对pair，而且是用关键字来查找、访问、插入和删除元素 
// vector是顺序容器，容器中存储的是单一类型元素，是按照位置顺序依次查找、访问、插入和删除元素
// map是为了“按值访问元素”的目的而设计的，底层数据结构是红黑树、哈希表，能够高效实现按照关键字进行访问、插入和删除等操作
// 容器中的元素是按关键字值存储的

// exercise_11_2
// 这道题在考察数据结构，在什么样的应用场景中最应该使用哪种数据结构
// list: 容器中保存的是自定义类型，存储的数量未知，需要频繁地插入删除操作，对元素的访问是顺序访问全部或是大部分，则list很合适
// vector: 动态数组，当需要存储的数据比较小（比如int等内置类型），需要存储的数量大致可知，基本在容器的末尾进行插入删除操作，
// 需要频繁地访问容器中任意位置，vector会带来最高的效率，如果需要频繁在容器的头部和尾部进行插入和删除操作，选择deque最佳
// map：需要建立键值对的集合，需要按值访问元素，当所存储的类型具有某种唯一性特征时，可以抽象出来作为元素的关键字类型
// 例如学生学号作为关键字类型，学生信息作为关联值，可以用学号来查找学生信息
// set：仅仅建立关键字的集合，一般是用来作为相应map中关键字的备注集合。顾名思义，就是集合类型，一般是满足或者是不满足某种条件的数据类型的集合

// exercise_11_3 is prog1_map_set()
void exercise_11_4(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    map<string, size_t> word_count;
    set<string> exclude = {"The", "But", "And", "Or", "An", "A",
                           "the", "but", "and", "or", "an", "a"};
    string word;
    while (infile >> word)
    {
        if(exclude.find(word) == exclude.end())
        {
            // eliminate punctuation and upper
            elimSymbol_Upper(word);
            ++word_count[word];
        }    
    }
    
    for (const auto &w : word_count)
    {
        cout << w.first << " occurs " << w.second
             << (w.second > 1 ? " times" : " time") << endl;
    }
    
    infile.close();
}

// exercise_11_5
// map和set都是关联容器，但是map中的元素是键值对，是pair;set's element is only key;
// 两者保存的关键字都是唯一的不能重复；但需要保存键值关系时，使用map，但仅仅保存key时就用set
// 一般来说，set是配合或者补充map而使用的，set是值的集合，map是键值对的集合；
// 如果只需判定给定值是否存在，使用set即可

// exercise_11_6
// set是关联容器，是按照关键字进行存储和访问的；list是顺序容器，是按照位置进行存储和访问的
// 两者有很多相同点，迭代器都是双向迭代器，有很多共同的操作，但是底层逻辑是不同的，一个是按照关键字，一个是按照位置 
// 当我需要存储关键字集合时，我使用set；当我需要存储一个普通集合时，而且需要进行多次插入删除操作，使用list
// 如果需要顺序访问，或者按照位置访问元素，使用list
// 如果需要快速判定是否集合中存在元素等于给定值，使用set

void exercise_11_7(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    map<string, vector<string>> families;
    string firName, secName;
    while (infile >> firName >> secName)
    {
        families[firName].push_back(secName);
        // if(families.find(firName) == families.end())
        //     families.insert(make_pair(firName, vector<string>{secName}));   // 可以直接使用列表初始化
        // else
        //     families.find(firName)->second.push_back(secName);
    }
    
    for (const auto &family : families)
    {
        string firN = family.first;
        for (const auto &sec : family.second)
        {
            cout << firN << "-" << sec << endl;
        }
    }

    infile.close();
}

void exercise_11_8(int argc, char *argv[])
{
    // 通过代码说明，set关联容器可以自动保持关键字唯一，而不需要自己判断，而且可以保证关键字有序
    // 从大到小排列，这些是顺序容器vector无法做到的
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    // put into vector to store non-duplication word
    vector<string> words;
    set<string> sset;
    string word;
    while (infile >> word)
    {
        if(find(words.cbegin(), words.cend(), word) == words.cend())
            words.push_back(word);

        sset.insert(word);
    }
    
    display(cout, words) << endl;
    display(cout, sset);
    
    infile.close();

// vector需要使用find算法顺序遍历容器检查待插入元素是否重复；而set由set模板负责检查元素是否重复，代码更简洁
// 更深层次的原因是vector是无序线性表，find算法是顺序查找，时间复杂度与vec.size()呈线性关系；而set的底层数据结构是红黑树，与容器大小呈对数关系，当数量足够大时，set的查找效率是considerable
// 当然vector可以保存元素的输入顺序，而set中的元素是从大到小有序存储的
}

void exercise_11_9(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    map<string, list<size_t>> word_tag;
    string line;
    size_t rowCnt = 1;
    while (getline(infile, line))
    {
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            word_tag[word].push_back(rowCnt);
        }
        ++rowCnt;
    }
    
    for (const auto &entry : word_tag)
    {
        cout << entry.first << " occurs in the ";
        for (auto row : entry.second)
        {
            cout << row << " ";
        }
        cout << (entry.second.size() > 1 ? "lines" : "line") << endl;
    }

    infile.close();
}

void exercise_11_10()
{
    // 首先我认为能够定义map<vector<int>::iterator, int>,但是不能定义map<list<int>::iterator, int>
    // 因为map的关键字要求提供operator<()的比较操作，vector<int>::iterator属于RandomAccess Iterator,有关系运算符
    // 但是list<int>::iterator属于Bidirection Iterator,没有定义operator<()
    vector<int> ivec = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    map<vector<int>::iterator, int> mapiter;
    for(auto iter = ivec.begin(); iter != ivec.end(); ++iter)
    {
        mapiter[iter] = *iter;
    }

    // list<int> ilst(ivec.cbegin(), ivec.cend());
    // map<list<int>::iterator, int> mapiterLst;
    // for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
    //     mapiterLst[iter] = *iter;   // 通过编译失败说明不可以定义这样的数据结构
}

// exercise_11_11 is prog3_key()

void exercise_11_12(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    vector<pair<string, double>> soldMsg;
    string book; double price;
    while (infile >> book >> price)
    {
        // exercise_11_13
        // 我认为{}列表初始化的创建pair对象形式最方便，最简单直接
        // soldMsg.push_back(make_pair(book, price));
        // soldMsg.push_back({book, price});
        soldMsg.push_back(pair<string, double>(book, price));
    }
    for (const auto &entry : soldMsg)
    {
        cout << entry.first << "\'s price is " << entry.second << endl; 
    }

    infile.close();
}

void exercise_11_14(int argc, char *argv[])
{
    checkargc(argc, 2);

    ifstream infile;
    openinfile(infile, argv[1]);

    map<string, vector<pair<string, string>>> families; // 从姓氏到每个孩子名字和生日的集合
    string firName, secName, birth;
    while (infile >> firName >> secName >> birth)
    {
        families[firName].push_back({secName, birth});
    }
    for (const auto &entry : families)
    {
        string family = entry.first;
        for (const auto &child : entry.second)
        {
            cout << family << " " << child.first
                 << " birthed in " << child.second << endl;
        }
    }

    infile.close();
}

// exercise_11_15
// map<int, vector<int> >::key_type is int; ::mapped_type is vector<int>
// ::value_type is pair<const int, vector<int> >;

void exercise_11_16()
{
    map<string, int> roster = { {"nanjiang", 24},
                                {"nanshouling", 53},
                                {"jianglijuan", 52}};
    
    auto iter = roster.begin();
    iter->second = 25;  // map's iterator can only modify second
    while (iter != roster.end())
    {
        cout << iter->first << " " << iter->second << endl;
        ++iter;
    }
}

void exercise_11_17()
{
    vector<string> v = {"lippman", "smith", "mailer",
                        "franz", "orlen", "ranier"};
    multiset<string> c;
    copy(v.begin(), v.end(), inserter(c, c.end()));  // this statement is right
    // copy(v.begin(), v.end(), back_inserter(c)); // this statement is error because multiset don't has push_back()
    cout << "after copy from vector to multiset: " << endl;
    display(cout, c) << endl;

    copy(c.begin(), c.end(), inserter(v, v.end()));
    cout << "after copy from multiset to vector:" << endl;
    display(cout, v) << endl;

    copy(c.begin(), c.end(), back_inserter(v));
    cout << "after copy again from multiset to vector:" << endl;
    display(cout, v);
}

// exercise_11_18
// map<string, size_t>::iterator

void exercise_11_20(int argc, char **argv)
{
    checkargc(argc, 2);

    ifstream infile;
    openinfile(infile, argv[1]);

    map<string, size_t> word_count;
    string word;
    while (infile >> word)
    {
        elimSymbol_Upper(word);
        // ++word_count[word];
        // 使用下标操作更容易编写和阅读，算法逻辑更符合使用下标操作
        auto ret = word_count.insert({word, 1});
        if(!ret.second)
            ++ret.first->second;    
    }
    for (const auto &entry : word_count)
    {
        cout << entry.first << " occurs " << entry.second
             << (entry.second > 1? " times." : " time.") << endl;
    }

    infile.close();
}

// exercise_11_21
// while(cin >> word) ++word_count.insert({word, 0}).first->second;
// which means if newWord don't in the map, then insert success, return pair<map<string,size_t>::iterator, bool>
// bool is true, then get NewInserter's element's second, then ++;
// if newWord exit in the map, the get aimElement's second, the ++.

// exercise_11_22
// map<string, vector<int>> wordIndex;
// pair<map<string, vector<int>>::iterator, bool> retit = wordIndex.insert({string(), {1, 2, 3}});

void exercise_11_23(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    multimap<string, string> families;  // pair<firstname, secondname>
    string firName, secName, birth;
    while (infile >> firName >> secName >> birth)
    {
        families.insert({firName, secName});
    }
    print(families);

    // 针对于multimap multiset来说，进行关键字查找会有多种方法
    cout << "Please input a family name which you want to know their children: ";
    string name;
    cin >> name;
    // method one:
    // auto total = families.count(name);
    // auto iter = families.find(name);
    // while (total)
    // {
    //     cout << iter->second << " ";
    //     --total;
    //     ++iter;
    // }
    // cout << endl;

    // method two
    // for(auto bgit = families.lower_bound(name),
    //          edit = families.upper_bound(name);
    //          bgit != edit; ++bgit)
    //     cout << bgit->second << " ";
    // cout << endl;

    // method three
    for(pair<map<string, string>::iterator, map<string, string>::iterator>
        range = families.equal_range(name); range.first != range.second; ++range.first)
        cout << range.first->second << " ";
    cout << endl;

    infile.close();
}

// exercise_11_24
// map<int, int> m;
// m[0] = 1; --> 1. search in the m for 0, but 0 doesn't exit;
// 2.insert a new pair<int,int>(0,0);
// 3.m[0] = 1;
// 因此完成了插入关键字0，并为其关联的值赋1

// exercise_11_25
// vector<int> v; v[0] = 1;
// 这是错的，发生了越界访问并赋值，编译时不会报错，甚至运行时也不会报错，但是发生了数组越界
// 这是“位置0”，而不是“关键字0”，如果vector中有不少于一个元素，则v[0]会返回第一个位置的元素的引用，并赋值为1；
// 若容器中没有元素，那么下表操作提取的是一个非法左值（下标不做范围检查），向其赋值可能导致系统崩溃等严重后果
void exercise_11_25()
{
    vector<int> v;
    v[0] = 1;
    // cout << v[0] << endl;
}

void exercise_11_26()
{
    // 可以用与map<>::key_type相容的类型进行下标访问
    // 下表运算符返回的类型是mapped_type的引用
    map<string, int> name_count = { {"lippman", 3}, {"smith", 5}};
    name_count["lippman"] += 10;

    print(name_count);
}

// exercise_11_27
// 在关联容器中查找一个关键字是否在容器中，而且又不想可能通过下标查找操作将本不在容器中的元素添加到容器中
// 此时使用find/count操作都可以；如果在multimap或者multiset中想要查找目标关键字的存在数量，使用count
// 若是需要查找关键字并对其关联的值进行访问或者修改，选择find

// exercise_11_28
// map<string, vector<int>> wordIndex;
// map<string, vector<int>>::iterator = wordIndex.find(word); 

// exercise_11_29
// 如果find的关键字不在容器中，那么lower_bound/upper_bound返回关键字的正确插入位置，不影响容器中关键字的排序
// equal_range返回pair<iterator, iterator>，其中first成员对应lower_bound返回的迭代器，second等于upper_bound返回的迭代器
// 当没有找到目标关键字时，两个迭代器的值是相等的，都指向目标关键字可以插入的位置，两个迭代器构成了一个空范围

// exercise_11_30
// pos.first->second返回的是equal_range返回的pair<>的first指向的迭代器所关联的值

void exercise_11_31_32(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);

    multimap<string, string> authors;
    string author, title;
    while (infile >> author && getline(infile, title))
    {
        auto pos = title.find_first_not_of(' ');
        title = title.substr(pos);
        authors.insert({author, title});
    }
    for (const auto &entry : authors)
    {
        cout << entry.first << " <<" << entry.second << ">>" << endl;
    }
    

    cout << "Please input a author name to delete author's first entry: ";
    author = "";
    cin >> author;
    auto boundit = authors.equal_range(author);
    if(boundit.first != boundit.second)
        authors.erase(boundit.first, boundit.second);
    else
        cout << author << " not found." << endl;

    cout << "after erase: " << endl;
    print(authors);

    infile.close();
}

// exercise_11_33 is prog7_text_convert

// exercise_11_34
// 结果是会将所有原来不在map<>转换规则中的单词全部转换为空串
// 因为使用下标运算符进行查找，原来不在容器中的关键字会被插入进去，所关联的字符串进行值初始化为空串
// 返回的转换结果永远是空串

// exercise_11_35
// 将trans_map[key] = value.substr(1) 转换成trans_map.insert({key, value.substr(1)});
// 本质上都是将新的单词转换规则添加到map中，但是如果规则文件中对于同一个单词有多条转换规则两种写法就会有差异
// 使用下标运算符，map中关键字所关联的字符串会是最后一条转换规则
// 而使用insert算法，map中关键字所关联的字符串会是第一条转换规则

// exercise_11_36
// 因为我进行了规则文件的合法性检测，所以一旦出现问题会抛出异常

// exercise_11_37
// 一个无序关联容器的元素的访问、插入、删除速度取决于哈希策略的质量，拥有高质量的哈希策略，
// 无序容器相比于有序容器会有更高的效率，如果一种数据没有有序条件，无序容器是最佳选择
// 有序容器的优势就是在于有序，可以在有序的基础上更方便地操作元素
// 无序版本通常性能更好，使用更简单，有序版本的唯一优势就是有序
// 当关键字类型没有明显的序关系时，或者维护元素的序关系代价比较大时，选择无序容器
// 当要求关键字有序存储时，选择有序关联容器

void exercise_11_38(int argc, char *argv[])
{
    // word_count program is prog8_unordered_map_set()
    checkargc(argc, 3);
    ifstream rulesFile, textFile;
    openinfile(rulesFile, argv[1]);
    openinfile(textFile, argv[2]);

    if(argc == 4)
    {
        ofstream outfile;
        openoutfile(outfile, argv[3]);
        wordConvertUnordered(rulesFile, textFile, outfile);

        outfile.close();
    }
    else
        wordConvertUnordered(rulesFile, textFile);
    
    rulesFile.close();
    textFile.close();
}

int main(int argc, char *argv[])
{
    // exercise_11_4(argc, argv);
    // exercise_11_7(argc, argv);
    // exercise_11_8(argc, argv);
    // exercise_11_9(argc, argv);
    // exercise_11_10();
    // exercise_11_12(argc, argv);
    // exercise_11_14(argc, argv);
    // exercise_11_16();
    // exercise_11_17();
    // exercise_11_20(argc, argv);
    // exercise_11_23(argc, argv);
    // exercise_11_25();
    // exercise_11_26();
    exercise_11_31_32(argc, argv);
    // exercise_11_38(argc, argv);

    return 0;
}