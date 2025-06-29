#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <queue>
#include "token.h"

class Scanner
{
private:
    std::string input;
    int first, current;
    std::queue<Token *> pending; // ! help us process the numbers separated from suffix u, l or combinations

public:
    Scanner(const char *in_s);
    Token *nextToken();
    void reset();
    ~Scanner();
};

void test_scanner(Scanner *scanner);

#endif