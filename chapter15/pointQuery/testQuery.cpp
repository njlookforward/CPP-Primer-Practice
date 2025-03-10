#include "Query.hpp"
#include "exercise.hpp"

using namespace std;

void test_WordQuery(int argc, char **argv)  // Bug8: 这绝对是马虎，argv也写成了argc
{
    checkInputArg(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);

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

int main(int argc, char **argv)
{
    // test_WordQuery(argc, argv);
    // test_NotQuery(argc, argv);
    // test_OrQuery(argc, argv);
    test_AndQuery(argc, argv);
    // test_complex(argc, argv);

    return 0;
}