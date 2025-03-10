#include "QueryResult.hpp"
using namespace std;

QueryResult::QueryResult(const string &word, shared_ptr<set<line_no>> pset, 
    strBlob ptext): _word(word), _pset(pset), _ptext(ptext) {}

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
    // if(!qr._pset)
    // {
    //     os << qr._word << " isn't found in the text.";
    //     return os;
    // }

    os << "In the text, " << qr._word << " occurs "
       << qr._pset->size() << " "
       << make_plural(qr._pset->size(), "time") << endl;
    
    // auto bgit = qr._pset->begin(),
    //      edit = qr._pset->end();
    
    // auto textbeg = qr._ptext->begin();
    // while (bgit != edit)
    // {
    //     os << "\tline (" << *bgit + 1 << "): "
    //        << *(textbeg + *bgit) << endl;
    //     ++bgit;
    // }
    
    for (auto lineNo : *qr._pset)
    {
        os << "\tline (" << lineNo + 1 << "): "
        //    << *(qr._ptext->begin() + lineNo) << endl;
           << qr._ptext.begin().deref(lineNo) << endl;
    }

    return os;
}