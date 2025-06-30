#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "visitor.h"

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << "Error: Incorrect number of arguments. Use: " << argv[0] << " <input_file>" << endl;
        exit(1);
    }

    ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        cout << "Error: Cannot open the file: " << argv[1] << endl;
        exit(1);
    }

    string input;
    string line;
    while (getline(infile, line))
    {
        input += line + '\n';
    }
    infile.close();

    Scanner scanner(input.c_str());

    string input_copy = input;
    Scanner scanner_test(input_copy.c_str());
    test_scanner(&scanner_test);
    cout << "Scanner works!!! :)" << endl;
    cout << endl;
    cout << "Initiating parsing:" << endl;
    Parser parser(&scanner);
    try
    {
        Program *program = parser.parseProgram();
        cout << "Parser works!!! :)" << endl
             << endl;
        cout << "Starting Visitor:" << endl;
        GenCodeVisitor input_code(std::cout);
        cout << "CODE: " << endl;
        input_code.generate(program);
        cout << endl;
        delete program;
    }
    catch (const exception &e)
    {
        cout << "Error during execution: " << e.what() << endl;
        return 1;
    }
    return 0;
}