#include "Query.hpp"
#include "exercise.hpp"
#include <array>

using namespace std;

void test_WordQuery(int argc, char **argv)  // Bug8: 这绝对是马虎，argv也写成了argc
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);   // 这个路径是相对于可执行程序所在的路径而设定的

    TextQuery text(infile);
    cout << "Executing Query for: ";
    string word;
    cin >> word;

    Query qr(word);
    cout << qr.eval(text);

    infile.close();
}

void test_NotQuery(int argc, char **argv)
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);

    TextQuery text(infile);

    cout << "Executing Query for: ";
    // input format: ~( alice )
    string word;
    char ch;
    cin >> ch >> ch >> word;

    Query res = ~Query(word);
    cout << res.eval(text);

    infile.close();
}

void test_OrQuery(int argc, char **argv)
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);

    TextQuery text(infile);

    cout << "Executing Query for: ";
    // input ( hair | alice )
    char ch;
    string lhs, rhs;
    cin >> ch >> lhs >> ch >> rhs;

    Query result = Query(lhs) | Query(rhs);
    cout << result.eval(text);

    infile.close();
}

void test_AndQuery(int argc, char **argv)
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);

    TextQuery text(infile);

    cout << "Executing Query for: ";
    // input ( hair & alice )
    char ch;
    string lhs, rhs;
    cin >> ch >> lhs >> ch >> rhs;

    Query result = Query(lhs) & Query(rhs);
    cout << result.eval(text);

    infile.close();
}

void test_complex(int argc, char **argv)
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);

    TextQuery text(infile);
    cout << "Executing Query for: ";
    string w1, w2, w3;
    char ch;
    // (( fiery & bird ) | wind)
    cin >> ch >> ch >> w1 >> ch >> w2 >> ch >> ch >> w3;
    Query result = ( Query(w1) & Query(w2) ) | Query(w3);
    cout << result.eval(text);

    infile.close();
}

void test_history(int argc, char **argv)
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);

    // include a history system which is a vector
    TextQuery text(infile);
    vector<array<string, 3>> history;

    while (true)
    {
        string sought1, sought2, sought3;
        if(!get_word(sought1)) break;
        if(sought1 != "h")
        {
            cout << "Please continue input the second and the third: ";
            cin >> sought2 >> sought3;
            history.push_back({sought1, sought2, sought3});

            Query res = Query(sought1) & Query(sought2) | Query(sought3);
            cout << "\tExecuting Query for: " << res << endl
                 << res.eval(text);
        } else {
            cout << "Please input Query No.";
            int i;
            cin >> i;
            if(i < 1 || i > history.size())
                throw out_of_range("Bad Query No.");
            else {
                Query res = Query(history[i - 1][0]) & Query(history[i - 1][1]) |
                            Query(history[i - 1][2]);
                cout << "history No." << i << "\'s record is as follow:" << endl
                     << "\tExecuting Query for " << res << endl
                     << res.eval(text);
            }
        }
    }

    infile.close();
}

int main(int argc, char **argv)
{
    // test_WordQuery(argc, argv);
    // test_NotQuery(argc, argv);
    // test_OrQuery(argc, argv);
    // test_AndQuery(argc, argv);
    // test_complex(argc, argv);
    test_history(argc, argv);

    return 0;
}