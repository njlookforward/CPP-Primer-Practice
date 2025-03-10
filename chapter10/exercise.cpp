#include "exercise.hpp"

void elimDups(vector<string> &words)
{
    // cout << "input sequence is: " << endl;
    // print(words);

    sort(words.begin(), words.end());
    // cout << "after sort sequence is: " << endl;
    // print(words);

    auto endit = unique(words.begin(), words.end());
    // cout << "after unique sequence is: " << endl;
    // print(words);

    words.erase(endit, words.end());
    // cout << "after erase sequence is: " << endl;
    // print(words);
}

void biggies(vector<string> &words, string::size_type sz,
             ostream &os, char delim)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), [](const string &a, const string &b)
                                             {   return a.size() < b.size(); });
    
    // auto bgit = find_if(words.cbegin(), words.cend(), SizeComp(sz));
    // auto bigit = find_if(words.cbegin(), words.cend(), [sz](const string &str)
    //                                         {   return str.size() >= sz;    });
    // auto count = words.cend() - bigit;
    // cout << count << " " << make_plural(count, "word", "s")
    //      << "'s length is no less than five length." << endl;
    
    // for_each(bigit, words.cend(), [](const string &str)
    //                         {   cout << str << " "; });
    // cout << endl;

    // use partition substitute find_if
    // exercise_10_18_19
    // auto endit = stable_partition(words.begin(), words.end(), [=](const string &str)
    //                                       {   return str.size() >= sz;    });   // 隐式捕获
    // exercise_10_25
    auto endit = stable_partition(words.begin(), words.end(),
                                  bind(isMoreThresholdLeng, placeholders::_1, sz));
    auto count = endit - words.begin();
    cout << count << " " << make_plural(count, "word", "s")
         << " of length is not less than 5 length." << endl;
    
    for_each(words.begin(), endit, [=, &os](const string &str)
                             {   os << str << delim; });    // 隐式捕获 + 显式值捕获列表
    cout << endl
         << "stable_partition sort: " << endl;
    print(words);
}

void elimDups(list<string> &slst)
{
    // use list's algorithm instead of generic algorithm will have more efficiency
    cout << "before sort: " << endl;
    print(slst);

    slst.sort();    // 使用<
    cout << "after sort: " << endl;
    print(slst);

    slst.unique();  // 直接删除重复单词
    cout << "after unique: " << endl;
    print(slst);
}
