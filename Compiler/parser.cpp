#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "exp.h"
#include "parser.h"

using namespace std;

bool Parser::match(Token::Type ttype)
{
    if (check(ttype))
    {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype)
{
    if (isAtEnd())
        return false;
    return current->type == ttype;
}

bool Parser::advance()
{
    if (!isAtEnd())
    {
        Token *temp = current;
        if (previous)
            delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR))
        {
            cout << "Error: not recognized character " << current->text << " during parsing." << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd()
{
    return (current->type == Token::END);
}

///////////////////////////////////////////////////////////////////////////////////

Parser::Parser(Scanner *sc) : scanner(sc)
{
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR)
    {
        cout << "Error: The first token " << current->text << " when parsing is not correct." << endl;
        exit(1);
    }
}

// * Program ::= VarDecList FunDecList
Program *Parser::parseProgram()
{
    Program *p = new Program();
    p->vardecs = parseVarDecList();
    p->fundecs = parseFunDecList();
    return p;
}

// * VarDecList ::= (VarDec_1)*
VarDecList *Parser::parseVarDecList()
{
    VarDecList *vdl = new VarDecList();
    VarDec *aux = parseVarDec();
    while (aux != nullptr)
    {
        vdl->add(aux);
        aux = parseVarDec();
    }
    return vdl;
}

// * FunDecList ::= (FunDec)+
FunDecList *Parser::parseFunDecList()
{
    FunDecList *fdl = new FunDecList();
    FunDec *aux = parseFunDec();
    while (aux != nullptr)
    {
        fdl->add(aux);
        aux = parseFunDec();
    }
    return fdl;
}

// * FunDec ::= fun id ([ParamDecList]) [: Type] {Body}
FunDec *Parser::parseFunDec()
{
    FunDec *fd = nullptr;

    if (match(Token::FUN))
    {
        FunDec *fun = new FunDec();

        if (!match(Token::ID))
        {
            cout << "Error: expected a name in the function declaration" << endl;
            exit(1);
        }

        fun->id = previous->text;

        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after the function name" << endl;
            exit(1);
        }

        // TODO: implement [ParamDecList] and [: Type]

        if (!match(Token::RP))
        {
            cout << "Error: expected a ')'" << endl;
            exit(1);
        }

        if (!match(Token::LB))
        {
            cout << "Error: expected a '{'" << endl;
            exit(1);
        }

        fun->b = parseBody();

        if (!match(Token::RB))
        {
            cout << "Error: expected a '}'" << endl;
            exit(1);
        }
    }

    return fd;
}