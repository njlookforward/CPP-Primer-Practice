#include "QueryResult.hpp"
using namespace std;

QueryResult::QueryResult(const string &word, shared_ptr<set<line_no>> pset, 
    shared_ptr<vector<string>> ptext): _word(word), _pset(pset), _ptext(ptext) {}

std::set<QueryResult::line_no>::const_iterator QueryResult::begin() const
{
    return _pset->cbegin();
}

std::set<QueryResult::line_no>::const_iterator QueryResult::end() const
{
    return _pset->cend();
}

std::ostream &operator<<(std::ostream &os, const QueryResult &qr)
{
    os << qr._word << " occurs "
       << qr._pset->size() << " "
       << make_plural(qr._pset->size(), "time") << endl;
    
    for (auto lineNo : *qr._pset)
    {
        os << "\t(line " << lineNo + 1 << "): "
           << *(qr._ptext->begin() + lineNo) << endl;
    }

    return os;
}