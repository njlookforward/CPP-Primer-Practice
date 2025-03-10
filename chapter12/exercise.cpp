#include "exercise.hpp"
using namespace std;

char *increTwice(char *oldpc, int &len)
{
    len *= 2;
    char *newpc = new char[len]();
    strcat(newpc, oldpc);
    delete [] oldpc;

    return newpc;
}