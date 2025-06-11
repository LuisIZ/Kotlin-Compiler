#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type
    {
        FUN,
        ID,
        LP, // (
        RP, // )
        LB, // {
        RB, // }
        COMMA,
        COLON, // :
        VAR,
        VAL,
        SEMICOLON, // ;
        ASSIGN,    // =
        PRINT,
        PRINTLN,
        IF,
        ELSE,
        FOR,
        IN,
        WHILE,
        RETURN,
        RANGE, // ..
        LT,    // <
        LE,    // <=
        EQ,    // ==
        PLUS,
        MINUS,
        MUL,
        DIV,
        TRUE,
        FALSE,
        NUM,
        END, // $ (end of program)
        ERR
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string &source, int first, int last);

    friend std::ostream &operator<<(std::ostream &outs, const Token &tok);
    friend std::ostream &operator<<(std::ostream &outs, const Token *tok);
};

#endif