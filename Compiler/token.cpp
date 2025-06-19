#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type) : type(type) { text = ""; }

Token::Token(Type type, char c) : type(type) { text = string(1, c); }

Token::Token(Type type, const string &source, int first, int last) : type(type)
{
    text = source.substr(first, last);
}

// ** This messages are for the scanner, when the scanner scans the input, is going to print the message TOKEN(...). If there is unknown token, the default state activates in the switch case 
std::ostream &operator<<(std::ostream &outs, const Token &tok)
{
    switch (tok.type)
    {

    // new tokens for FunDecl
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
    case Token::COLON:
        outs << "TOKEN(COLON)";
        break;
    case Token::LB:
        outs << "TOKEN(LB)";
        break;
    case Token::RB:
        outs << "TOKEN(RB)";
        break;

    // new tokens for rule ParamDecList
    case Token::COMMA:
        outs << "TOKEN(COMMA)";
        break;

    // new tokens for rule VarDec_1
    case Token::VAR:
        outs << "TOKEN(VAR)";
        break;
    case Token::VAL:
        outs << "TOKEN(VAL)";
        break;
    case Token::SEMICOLON:
        outs << "TOKEN(SEMICOLON)";
        break;

    // new tokens for rule AugAssign
    case Token::AA_PLUS:
        outs << "TOKEN(AA_PLUS)";
        break;
    case Token::AA_MINUS:
        outs << "TOKEN(AA_MINUS)";
        break;
    case Token::AA_MUL:
        outs << "TOKEN(AA_MUL)";
        break;
    case Token::AA_DIV:
        outs << "TOKEN(AA_DIV)";
        break;
    case Token::AA_MOD:
        outs << "TOKEN(AA_MOD)";
        break;

    // new tokens for rule Stm
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

    // new tokens for rule ForRangeExp
    case Token::RANGE:
        outs << "TOKEN(RANGE)";
        break;
    case Token::STEP:
        outs << "TOKEN(STEP)";
        break;

    // new tokens for rule CExp
    case Token::LT:
        outs << "TOKEN(LT)";
        break;
    case Token::LE:
        outs << "TOKEN(LE)";
        break;
    case Token::GT:
        outs << "TOKEN(GT)";
        break;
    case Token::GE:
        outs << "TOKEN(GE)";
        break;
    case Token::EQ:
        outs << "TOKEN(EQ)";
        break;
    case Token::DIFF:
        outs << "TOKEN(DIFF)";
        break;

    // new tokens for rule LogicalExp
    case Token::LOG_AND:
        outs << "TOKEN(LOG_AND)";
        break;
    case Token::LOG_OR:
        outs << "TOKEN(LOG_OR)";
        break;

    // new token for rule OrExp
    case Token::BW_OR:
        outs << "TOKEN(BW_OR)";
        break;

    // new token for rule XorExp
    case Token::BW_XOR:
        outs << "TOKEN(BW_XOR)";
        break;

    // new token for rule AndExp
    case Token::BW_AND:
        outs << "TOKEN(BW_AND)";
        break;

    // new tokens for rule ShiftExp
    case Token::BW_SHL:
        outs << "TOKEN(BW_SHL)";
        break;
    case Token::BW_SHR:
        outs << "TOKEN(BW_SHR)";
        break;
    case Token::BW_USHR:
        outs << "TOKEN(BW_USHR)";
        break;

    // new tokens for rule Exp
    case Token::PLUS:
        outs << "TOKEN(PLUS)";
        break;
    case Token::MINUS:
        outs << "TOKEN(MINUS)";
        break;

    // new tokens for rule Term
    case Token::MUL:
        outs << "TOKEN(MUL)";
        break;
    case Token::DIV:
        outs << "TOKEN(DIV)";
        break;
    case Token::MOD:
        outs << "TOKEN(MOD)";
        break;

    // new tokens for rule PrefixOp
    case Token::NOT:
        outs << "TOKEN(NOT)";
        break;
    case Token::PRE_INC:
        outs << "TOKEN(PRE_INC)";
        break;
    case Token::PRE_DEC:
        outs << "TOKEN(PRE_DEC)";
        break;
    case Token::INV:
        outs << "TOKEN(INV)";
        break;

    // new tokens for rule Factor
    case Token::POINT:
        outs << "TOKEN(POINT)";
        break;
    case Token::TO_BYTE:
        outs << "TOKEN(TO_BYTE)";
        break;
    case Token::TO_SHORT:
        outs << "TOKEN(TO_SHORT)";
        break;
    case Token::TO_INT:
        outs << "TOKEN(TO_INT)";
        break;
    case Token::TO_LONG:
        outs << "TOKEN(TO_LONG)";
        break;
    case Token::TO_U_BYTE:
        outs << "TOKEN(TO_U_BYTE)";
        break;
    case Token::TO_U_SHORT:
        outs << "TOKEN(TO_U_SHORT)";
        break;
    case Token::TO_U_INT:
        outs << "TOKEN(TO_U_INT)";
        break;
    case Token::TO_U_LONG:
        outs << "TOKEN(TO_U_LONG)";
        break;

    // new tokens for rule Bool
    case Token::TRUE:
        outs << "TOKEN(TRUE)";
        break;
    case Token::FALSE:
        outs << "TOKEN(FALSE)";
        break;

    // new tokens for rule Num
    case Token::SUFFIX_u:
        outs << "TOKEN(SUFFIX_u)";
        break;
    case Token::SUFFIX_U:
        outs << "TOKEN(SUFFIX_U)";
        break;
    case Token::SUFFIX_l:
        outs << "TOKEN(SUFFIX_l)";
        break;
    case Token::SUFFIX_L:
        outs << "TOKEN(SUFFIX_L)";
        break;

    // new token for rule Digit
    case Token::NUM:
        outs << "TOKEN(NUM)";
        break;

    // new extra tokens (outside grammar)
    case Token::END:
        outs << "TOKEN(END)";
        break;
    case Token::ERR:
        outs << "TOKEN(ERR)";
        break;
    case Token::STRING:
        outs << "TOKEN(STRING)";
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