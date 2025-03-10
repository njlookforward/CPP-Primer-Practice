#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <utility>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "Sales_data.hpp"

using namespace std;

void openinfile(ifstream &ifs, const string &dir);
void openoutfile(ofstream &ofs, const string &dir);
void elimSymbol_Upper(std::string &word);

template <typename Container>
ostream &display(ostream &os, const Container &con)
{
    for (const auto &elem : con)
    {
        os << elem << " ";
    }
    os << endl;

    return os;
}

inline bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

template <typename MapType>
inline void print(MapType &con) // maybe map, maybe multimap
{
    for(auto iter = con.begin(); iter != con.end(); ++iter)
        cout << iter->first << " " << iter->second << endl;
}

inline void checkargc(int argc, int reqNum)
{
    if(argc < reqNum)
    {
        ostringstream oss;
        oss << "Please input requested " << reqNum << " parameters.";
        throw runtime_error(oss.str());
    }
}

void textConvert(istream &ruleFile, istream &textFile, ostream &os = cout);
void buildTransRules(istream &ruleFile, map<string, string> &transRules);
void transText(istream &textFile, ostream &os, map<string, string> &transRules);

// 无需容器的hash函数
inline size_t hasher(const Sales_data &sd)
{
    return hash<string>() (sd.isbn());
}

void wordConvertUnordered(istream &ruleFile, istream &textFile, ostream &os = cout);
void buildTransRules(istream &ruleFile, unordered_map<string, string> &transRules);
const string &transform(const string &word, const unordered_map<string, string> &transRules);

#endif