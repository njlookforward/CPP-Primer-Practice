#include "exercise.hpp"

using namespace std;

void openfile(std::ifstream &ifs, const std::string &dir)
{
    ifs.open(dir);
    if(!ifs)
    {
        cerr << "Sorry, cannot open " << dir << endl;
        exit(-1);
    }
}

std::string cleanup_str(const std::string &word)
{
    string ret;
    for(auto iter = word.begin(); iter != word.end(); ++iter)
    {
        // 需要过滤所有的标点，将大写字母变成小写进行统一
        if(ispunct(*iter))
            continue;
        
        ret += tolower(*iter);
    }

    return ret;
}

bool Factor(int num, const std::vector<int> &ivec)
{
    modulus<int> intMod;
    for (auto &f : ivec)
    {
        if(intMod(num, f))
            return false;
    }
    return true;
}
