#include <iostream>
#include <cstring>
#include "token.h"
#include "scanner.h"

using namespace std;

Scanner::Scanner(const char *s) : input(s), first(0), current(0) {}

bool is_white_space(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

Token *Scanner::nextToken()
{
    Token *token;
    while (current < input.length() && is_white_space(input[current]))
        current++;
    if (current >= input.length())
        return new Token(Token::END);
    char c = input[current];
    first = current;
    if (isdigit(c))
    {
        current++;
        while (current < input.length() && isdigit(input[current]))
            current++;
        token = new Token(Token::NUM, input, first, current - first);
    }
}

void Scanner::reset()
{
    first = 0;
    current = 0;
}

void test_scanner(Scanner *scanner)
{
    Token *current;
    cout << "Initiating Scanner:" << endl
         << endl;
    while ((current = scanner->nextToken())->type != Token::END)
    {
        if (current->type == Token::ERR)
        {
            cout << "Error in scanner - invalid character: " << current->text << endl;
            break;
        }
        else
        {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END)" << endl;
    delete current;
}