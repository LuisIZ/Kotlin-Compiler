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
        COMMA, // ,

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

        /*
        ! los unary add y minus no har problema en el scanner, se tendria que lidiar en el parser y ya no seria necesario estos tokens...
        */

        // new tokens for rule PrefixOp
        UNARY_ADD,   // for example: +a
        UNARY_MINUS, // for example: -a
        NOT,         // !
        PRE_INC,     // for example: ++a
        PRE_DEC,     // for example: --a
        INV,         // inv

        /*
        ! el ++ y el -- mejor no diferenciarlos como sufijo o prefijo, uno nomas :v
        */

        // new tokens for rule PostfixOp
        POST_INC, // for example: a++
        POST_DEC, // for example: a--

        // new tokens for rule Factor
        POINT,      // .
        TO_BYTE,    // .toByte
        TO_SHORT,   // .toShort
        TO_INT,     // .toInt
        TO_LONG,    // .toLong
        TO_U_BYTE,  // .toUByte
        TO_U_SHORT, // .toUShort
        TO_U_INT,   // .toUInt
        TO_U_LONG,  // .toULong

        // new tokens for rule Bool
        TRUE,
        FALSE,

        // new tokens for rule Num
        SUFFIX_u, // u
        SUFFIX_U, // U
        SUFFIX_l, // l
        SUFFIX_L, // L

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

#endif