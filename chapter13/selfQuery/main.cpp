#include <iostream>
#include <fstream>
#include "TextQuery.hpp"
#include <memory>
using namespace std;


void Query(int argc, char *argv[])
{
    // checkargc(argc, 2);
    ifstream infile(argv[1]);
    if(!infile)
    {
        cerr << "Sorry, cannot open " << argv[1] << endl;
        return;
    }
    shared_ptr<ifstream> pf(&infile, [] (ifstream *pf) {    pf->close();    });

    TextQuery tq(infile);
    do {
        cout << "Please input a word to query or 'q' to exit: ";
        String word;
        if(!(cin >> word) || word == "q")
            break;
        
        cout << tq.query(word) << endl;
    } while(true);
}

int main(int argc, char **argv)
{
    Query(argc, argv);

    return 0;
}