#ifndef MAXCNTWORD_HPP_
#define MAXCNTWORD_HPP_

#include <string>
using namespace std;

class MaxCntWord
{
public:
    MaxCntWord() = default;
    ~MaxCntWord() {};

    const string &word() const  {   return _word;   }
    int occur() const   {   return _occur;  }

    void word(string newWord)   {   _word = newWord;    }
    void occur(int newOccur)    {   _occur = newOccur;  }
    void upgrade(string newWord, int newOccur)
    {
        word(newWord);
        occur(newOccur);
    }

    bool isValid() const    {   return !_word.empty();  }

private:
    string _word;
    int _occur = 1;
};  // never forget to use ; end class definition

#endif