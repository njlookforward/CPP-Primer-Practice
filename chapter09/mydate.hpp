#ifndef MYDATE_HPP
#define MYDATE_HPP

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

extern string month_name[12];
extern string month_abbr[12];
extern unsigned month_days[13];

class mydate {
public:
    mydate() = default;
    mydate(const string &date);

    unsigned year() const   {   return _year;   }
    unsigned month() const  {   return _month;  }
    unsigned day() const    {   return _day;    }

private:
    unsigned _year;
    unsigned _month;
    unsigned _day;
};

unsigned get_month(const string &ds, string::size_type &pos);
unsigned get_day(const string &ds, unsigned mon, string::size_type &pos);
unsigned get_year(const string &ds, string::size_type &pos);
ostream &operator<<(ostream &os, const mydate &date);

#endif