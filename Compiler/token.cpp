#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type) : type(type) { text = ""; }

Token::Token(Type type, char c) : type(type) { text = string(1, c); }

Token::Token(Type type, const string &source, int first, int last) : type(type)
{
    text = source.substr(first, last);
}

std::ostream &operator<<(std::ostream &outs, const Token &tok)
{
    switch (tok.type)
    {
        case Token::FUN:
            outs << "TOKEN(FUN)";
            break;
        case Token::ID:
            outs << "TOKEN(ID)";
            break;
        case Token::LP:
            outs << "TOKEN(LP)";
            break;
        case Token::RP:
            outs << "TOKEN(RP)";
            break;
        case Token::LB:
            outs << "TOKEN(LB)";
            break;
        case Token::RB:
            outs << "TOKEN(RB)";
            break;
        case Token::COMMA:
            outs << "TOKEN(COMMA)";
            break;
        case Token::COLON:
            outs << "TOKEN(COLON)";
            break;
        case Token::VAR:
            outs << "TOKEN(VAR)";
            break;
        case Token::VAL:
            outs << "TOKEN(VAL)";
            break;
        case Token::SEMICOLON:
            outs << "TOKEN(SEMICOLON)";
            break;
        case Token::ASSIGN:
            outs << "TOKEN(ASSIGN)";
            break;
        case Token::PRINT:
            outs << "TOKEN(PRINT)";
            break;
        case Token::PRINTLN:
            outs << "TOKEN(PRINTLN)";
            break;
        case Token::IF:
            outs << "TOKEN(IF)";
            break;
        case Token::ELSE:
            outs << "TOKEN(ELSE)";
            break;
        case Token::FOR:
            outs << "TOKEN(FOR)";
            break;
        case Token::IN:
            outs << "TOKEN(IN)";
            break;
        case Token::WHILE:
            outs << "TOKEN(WHILE)";
            break;
        case Token::RETURN:
            outs << "TOKEN(RETURN)";
            break;
        case Token::RANGE:
            outs << "TOKEN(RANGE)";
            break;
        case Token::LT:
            outs << "TOKEN(LT)";
            break;
        case Token::LE:
            outs << "TOKEN(LE)";
            break;
        case Token::EQ:
            outs << "TOKEN(EQ)";
            break;
        case Token::PLUS:
            outs << "TOKEN(PLUS)";
            break;
        case Token::MINUS:
            outs << "TOKEN(MINUS)";
            break;
        case Token::MUL:
            outs << "TOKEN(MUL)";
            break;
        case Token::DIV:
            outs << "TOKEN(DIV)";
            break;
        case Token::TRUE:
            outs << "TOKEN(TRUE)";
            break;
        case Token::FALSE:
            outs << "TOKEN(FALSE)";
            break;
        case Token::END:
            outs << "TOKEN(END)";
            break;
        case Token::ERR:
            outs << "TOKEN(ERR)";
            break;
        default:
            outs << "TOKEN(UNKNOWN)";
            break;
    }
    return outs;
}

std::ostream &operator<<(std::ostream &outs, const Token *tok)
{
    return outs << *tok;
}