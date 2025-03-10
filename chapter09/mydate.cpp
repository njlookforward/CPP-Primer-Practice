#include "mydate.hpp"

string month_name[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

string month_abbr[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"
};

unsigned month_days[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

mydate::mydate(const string &date)
{
    string::size_type pos = 0,      // 字符串位置，用来扫描
                      numlen = 0;   // 数字长度
    
    if((pos = date.find_first_of("0123456789", pos)) == string::npos)
        throw invalid_argument("no number.");
    
    if(pos > 0)     // 月份名
    {
        _month = get_month(date, pos);
        _day = get_day(date, _month, pos);
        if(date[pos] != ' ' && date[pos] != ',')    // 逻辑搞错了
            throw invalid_argument("invalid delimit -> non-, -");
        ++pos;
        _year = get_year(date, pos); 
    }
    else            // 月份值
    {
        _month = stoi(date, &numlen);
        if(_month < 1 || _month > 12)
            throw invalid_argument("invalid month");    // 忘记了一种错误情况处理
        pos = numlen;
        if(date[pos++] != '/')
            throw invalid_argument("invalid delimit -> non-/-");
        _day = get_day(date, _month, pos);
        if(date[pos++] != '/')
            throw invalid_argument("invalid delimit -> non-/-");
        _year = get_year(date, pos);
    }
}

unsigned get_month(const string &ds, string::size_type &pos)
{
    // 准确来说这个部分就是字符匹配
    size_t i = 0,   // being used to store month's index
           j = 0;   // being used to scan month's character
    for(; i < 12; ++i)
    {
        for(pos = 0, j = 0; j < month_abbr[i].size(); ++j, ++pos)
        {
            if(ds[pos] != month_abbr[i][j])
                break;
        }
        if(j == month_abbr[i].size())
            break;  // 说明匹配成功了
    }
    if(i == 12)
        throw invalid_argument("input month is error, please check seriously.");
    
    if(ds[pos] == ' ')  // 说明是简写月份，已经找到了
    {
        ++pos;
        return i + 1;
    }
    for(; j < month_name[i].size(); ++j, ++pos) // 需要继续在完成月份名称中进行检查
    {
        if(ds[pos] != month_name[i][j])
            throw invalid_argument("input month is error, please check seriously.");
    }
    if(ds[pos] == ' ')
    {
        ++pos;
        return i + 1;
    } else
        throw invalid_argument("input month is error, please check seriously.");
}

unsigned get_day(const string &ds, unsigned mon, string::size_type &pos)
{
    string::size_type len;
    unsigned day = stoi(ds.substr(pos), &len);
    if(day > 0 && day <= month_days[mon])
    {
        pos += len;
        return day;
    }
    else
        throw invalid_argument("day is invalid.");
}

unsigned get_year(const string &ds, string::size_type &pos)
{
    string::size_type len;
    unsigned year = stoi(ds.substr(pos), &len);
    pos += len;
    if(pos == ds.size())    // 到达字符串末尾
        return year;
    else
        throw invalid_argument("in the end of date has invalid characters.");
}

ostream &operator<<(ostream &os, const mydate &date)
{
    os << date.year() << "-" << date.month() << "-"
       << date.day();

    return os;
}
