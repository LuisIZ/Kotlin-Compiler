#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// ** I comment the rules in which for the first time a token appears
// ** Also, I comment some tokens to understand what they are
class Token
{
public:
    enum Type
    {

        // new tokens for FunDecl
        FUN,
        ID,
        LP,    // (
        RP,    // )
        COLON, // :
        LB,    // {
        RB,    // }

        // new tokens for rule ParamDecList
        COMMA,

        // new tokens for rule VarDec_1
        VAR,
        VAL,
        SEMICOLON, // ;

        // new tokens for rule AugAssign
        AA_PLUS,  // +=
        AA_MINUS, // -=
        AA_MUL,   // *=
        AA_DIV,   // /=
        AA_MOD,   // %=

        // new tokens for rule Stm
        ASSIGN, // =
        PRINTLN,
        PRINT,
        IF,
        ELSE,
        FOR,
        IN,
        WHILE,
        RETURN,

        // new tokens for rule ForRangeExp
        RANGE, // ..
        STEP,

        // new tokens for rule CExp
        LT,   // <
        LE,   // <=
        GT,   // >
        GE,   // >=
        EQ,   // ==
        DIFF, // !=

        // new tokens for rule LogicalExp
        LOG_AND, // &&
        LOG_OR,  // ||

        // new token for rule OrExp
        BW_OR, // or

        // new token for rule XorExp
        BW_XOR, // xor

        // new token for rule AndExp
        BW_AND, // and

        // new tokens for rule ShiftExp
        BW_SHL,  // shL
        BW_SHR,  // shr
        BW_USHR, // ushr

        // new tokens for rule Exp
        PLUS,
        MINUS,

        // new tokens for rule Term
        MUL,
        DIV,
        MOD,

        // new tokens for rule PrefixOp
        UNARY_ADD,   // for example: +a
        UNARY_MINUS, // for example: -a
        NOT,         // !
        PRE_INC,     // for example: ++a
        PRE_DEC,     // for example: --a
        INV,         // inv

        // new tokens for rule PostfixOp
        POST_INC, // for example: a++
        POST_DEC, // for example: a--

        // new tokens for rule Factor
        TO_BYTE,
        TO_SHORT,
        TO_INT,
        TO_LONG,
        TO_U_BYTE,
        TO_U_SHORT,
        TO_U_INT,
        TO_U_LONG,

        // new tokens for rule Bool
        TRUE,
        FALSE,

        // new tokens for rule Num
        SUFFIX_u,
        SUFFIX_U,
        SUFFIX_l,
        SUFFIX_L,

        // new token for rule Digit
        NUM,

        // new extra tokens (outside grammar)
        END, // $ (end of program)
        ERR  // error (for debugging)
    };

    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string &source, int first, int last);

    friend std::ostream &operator<<(std::ostream &outs, const Token &tok);
    friend std::ostream &operator<<(std::ostream &outs, const Token *tok);
};

#endif // TOKEN_H