#include "Person.hpp"
using namespace std;

Person::Person(const string &name, const string &addr):
    _name(name), _address(addr) {}

istream &read(istream &is, Person &rhs)
{
    is >> rhs._name >> rhs._address;
    return is;
}

ostream &print(ostream &os, const Person &rhs)
{
    os << rhs.name() << " " << rhs.address();
    return os;
}