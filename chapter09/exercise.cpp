#include "exercise.hpp"

bool find_v1(vector<int>::const_iterator first, vector<int>::const_iterator last, int aim)
{
    auto iter = find(first, last, aim);
    return iter != last;
}

auto find_v2(vector<int>::const_iterator first, vector<int>::const_iterator last, int aim) -> vector<int>::const_iterator
{
    // return find(first, last, aim);
    // 练习的本意应该是让自己书写算法流程，着重要考虑到没有找到元素时的处理情况
    while (first != last)
    {
        if(*first == aim)
            return first;
        else
            ++first;    
    }
    return last;
}

bool isEqual(const list<int> &ilst, const vector<int> &ivec)
{
    if (ilst.size() != ivec.size())
    {
        return false;
    }
    else
    {
        auto lstbeg = ilst.cbegin(),
             lstend = ilst.cend();
        auto vecbeg = ivec.cbegin();
        
        while (lstbeg != lstend)
        {
            if(*lstbeg != *vecbeg)
                return false;
            else
            {
                ++lstbeg;
                ++vecbeg;
            }    
        }
        return true;
    }   
}

forward_list<string>::iterator Insert(forward_list<string> &sfLst, const string &posElem, const string &newElem)
{
    auto curit = sfLst.begin(),
         previt = sfLst.before_begin();
    while (curit != sfLst.end())
    {
        if(*curit == posElem)
            return sfLst.insert_after(curit, newElem);
        else
        {
            ++previt;
            ++curit;
        }
    }
    return sfLst.insert_after(previt, newElem);
}

string Initstr(const vector<char> &cvec)
{
    return string(cvec.begin(), cvec.end());
}

void ModifyStr(string &str, const string &oldVal, const string &newVal)
{
    // this is using subscript to modify
    // string::size_type aimPos = 0;
    // while ((aimPos = str.find(oldVal, aimPos)) != string::npos)
    // {
    //     str.erase(aimPos, oldVal.size());
    //     str.insert(aimPos, newVal);
    //     aimPos += newVal.size();
    // }

    // use iterator to erase and insert string, notice update iterator after erase and insert
    string::iterator bgit = str.begin();
    while ((bgit = search(bgit, str.end(), oldVal.begin(), oldVal.end())) != str.end())
    {
        bgit = str.erase(bgit, bgit + oldVal.size());
        bgit = str.insert(bgit, newVal.begin(), newVal.end());
        bgit += newVal.size();
    }
}

void ModifyStrAns(string &str, const string &oldVal, const string &newVal)
{
    auto len = oldVal.size();
    if(!len)
    {
        cerr << "oldVal can't be a empty string." << endl;
        return;
    }

    auto iter = str.begin();
    while (iter <= str.end() - len) // 末尾小于oldVal的部分没有必要进行检查
    {
        auto iter1 = iter;
        auto oldit = oldVal.begin();    // 每次都要从头开始比
        while (oldit != oldVal.end() && *iter1 == *oldit)
        {
            ++iter1;
            ++oldit;
        }
        if(oldit == oldVal.end())
        {
            // find substr is equal to oldVal
            iter = str.erase(iter, iter1);
            iter = str.insert(iter, newVal.begin(), newVal.end());
            iter += newVal.size();
        } else 
            ++iter;
    }
}

void ModifyStr_v2(string &str, const string &oldVal, const string &newVal)
{
    // 这次要求使用下标和replace
    string::size_type aimPos = 0;
    while ((aimPos = str.find(oldVal, aimPos)) != string::npos)
    {
        str.replace(aimPos, oldVal.size(), newVal);
        aimPos += newVal.size();
    }
}

void ModifyStr_v3(string &name, const string &pre, const string &post)
{
    // use iterator and insert and append add pre and post
    name.insert(name.begin(), 1, ' ');
    name.insert(name.begin(), pre.begin(), pre.end());
    name.append(" ");
    name.append(post);
}

void ModifyStr_v4(string &name, const string &pre, const string &post)
{
    name.insert(0, 1, ' ');
    name.insert(0, pre);
    name.insert(name.size(), " ");
    name.insert(name.size(), post);
}

void find_num_alpha(const string &str)
{
    string numbers("0123456789"),
            alphabet("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");
    // cout << alphabet.size();
    string::size_type pos = 0;
    while ((pos = str.find_first_of(numbers, pos)) != string::npos)
    {
        cout << "found number at index " << pos
             << " element is " << str[pos] << endl;
        ++pos;    
    }
    pos = 0;
    while ((pos = str.find_first_of(alphabet, pos)) != string::npos)
    {
        cout << "found alpha at index " << pos
             << " element is " << str[pos] << endl;
        ++pos;    
    }
}

void find_num_alpha_v2(const string &str)
{
    string numbers("0123456789"),
           alphabet("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");

    string::size_type pos = 0;
    while ((pos = str.find_first_not_of(alphabet, pos)) != string::npos)
    {
        cout << "found number at index " << pos
             << " element is " << str[pos] << endl;
        ++pos;  
    }

    pos = 0;
    while ((pos = str.find_first_not_of(numbers, pos)) != string::npos)
    {
        cout << "found alpha at index " << pos
             << " element is " << str[pos] << endl;
        ++pos;  
    }
}
bool exclude_ascender_descender(const string &word)
{
    string ascender("bdfhijklt"),
           descender("gjpqy");  // notification: capital letter don't belong ascender
    auto ascPos = word.find_first_of(ascender),
         desPos = word.find_first_of(descender);
    if(ascPos == string::npos && desPos == string::npos)
        return true;
    else
        return false;
}

int calculateStr(const vector<string> &svec)
{
    int sum = 0, cur;
    for (auto &intStr : svec)
    {
        cur = stoi(intStr);
        sum += cur;
    }
    return sum;
}

double calStr_v2(const vector<string> &svec)
{
    double sum = 0.0, cur;
    for (auto &douStr : svec)
    {
        cur = stod(douStr);
        sum += cur;
    }
    return sum;
}

map<string, unsigned> monthmap{
    {"January", 1}, {"Jan", 1}, {"February", 2}, {"Feb", 2},
    {"March", 3}, {"Mar", 3}, {"April", 4}, {"Apr", 4},
    {"May", 5}, {"June", 6}, {"Jun", 6}, {"July", 7}, {"Jul", 7},
    {"August", 8}, {"Aug", 8}, {"September", 9}, {"Sep", 9},
    {"October", 10}, {"Oct", 10}, {"November", 11}, {"Nov", 11},
    {"December", 12}, {"Dec", 12}
};

Date::Date(const string &date)
{
    istringstream iss(date);

    string::size_type pos = 0;
    if((pos = date.find('/')) != string::npos)
    {
        // process 1/1/1900
        char part[20] = {};
        iss.get(part, 20, '/');
        iss.ignore(1);  // 字符串流不会释放'/',需要手动删除
        _month = stoi(part);
        iss.get(part, 20, '/');
        iss.ignore(1);
        _day = stoi(part);
        iss.get(part, 20);
        _year = stoi(part);
    }
    else
    {
        // process Jan 1 1900  or January 1, 1900 
        string part;
        iss >> part;
        _month = monthmap[part];
        iss >> part;
        _day = stoi(part);
        iss >> part;
        _year = stoi(part);
    }
}

ostream &operator<<(ostream &os, const Date &date)
{
    os << date._year << "-" << date._month << "-" << date._day;
    return os;
}

void calNewVal(stack<obj> &so, double val)
{
    // this part merely is to process val into stack
    if(so.empty() || so.top()._t == LP)
        so.push(obj(VAL, val));
    else if(so.top()._t == VAL)
        throw invalid_argument("in the middle of operand don't have operation.");
    else if(so.top()._t == ADD)
    {
        so.pop();
        double lval = so.top()._v;
        so.pop();
        val += lval;
        so.push(obj(VAL, val));
    }
    else if (so.top()._t == SUB)
    {
        so.pop();
        double lval = so.top()._v;
        so.pop();
        lval -= val;
        so.push(obj(VAL, lval));
    }
}

double expresolution(const string &expr)
{
    string::size_type pos = 0,      // locate the character in the expression, being used to scan whole expression
                      numlen = 0;   // being used to store number's length
    stack<obj> so;  // store operand

    skipws(expr, pos);
    while (pos != expr.size() && pos != string::npos)   // 边界要考虑全面
    {
        if(expr[pos] == '(')
        {
            if(so.empty() || so.top()._t == LP || so.top()._t == ADD || so.top()._t == SUB)
                so.push(obj(LP));
            else if(so.top()._t == VAL)
                throw invalid_argument("in the middle of two operand don't have operation.");
            ++pos;
            skipws(expr,pos);
        }
        else if (expr[pos] == ')')
        {
            if(so.empty())
                throw invalid_argument("don't have left parenthesis.");
            else if(so.top()._t == LP)
                throw invalid_argument("empty parenthesis.");
            else if(so.top()._t == ADD || so.top()._t == SUB)
                throw invalid_argument("wrong expression.");
            else if (so.top()._t == VAL)
            {
                double val = so.top()._v;
                so.pop();
                if(so.top()._t == LP)
                {
                    so.pop();
                    calNewVal(so, val); // 将括号的结果压入栈中
                }
                else
                    throw invalid_argument("parenthesis mismatch.");
            }
            ++pos;
            skipws(expr, pos);
        }
        else if (expr[pos] == '+' || expr[pos] == '-')  // 这里出问题了
        {
            if(so.empty() || so.top()._t == LP || so.top()._t == ADD || so.top()._t == SUB)
                throw invalid_argument("wrong expression.");
            else if (so.top()._t == VAL)
            {
                if (expr[pos] == '+')   // 这里忘记改成+
                    so.push(obj(ADD));
                else
                    so.push(obj(SUB));
            }
            ++pos;
            skipws(expr, pos);
        }
        else
        {
            // 此时肯定处理的是数字，而不可能是空白字符
            double val = stod(expr.substr(pos), &numlen);   // 这里出问题，应该是转换子字符串，而不是全部
            pos += numlen;
            skipws(expr, pos);  
            calNewVal(so, val);
        }
    }
    // 表达式全部扫描完全后，此时栈中应该只有唯一的一个值
    if(so.size() == 1 && so.top()._t == VAL)    // 必须要考虑全面
        return so.top()._v;
    else
        throw invalid_argument("expression resolution failed.");
}

// 哪怕只有一秒钟，一分钟，一小时也是一种重大胜利，不要在乎时长，不要磨洋工，认认真真过好当下的每一秒钟
// 一道题一道题的练，一个字一个字地看，一行行地看，一步一步地走，走得坚实而有力量，拿出你的激情