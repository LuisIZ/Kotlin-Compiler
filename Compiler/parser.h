#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "exp.h"

class Parser
{
private:

    // * scanner stuff for checking tokens
    Scanner *scanner;
    Token *current, *previous;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    bool advance();
    bool isAtEnd();

    // ? It is a list of stms just to keep record of each stm created in the program, like a memory?
    list<Stm *> parseStmList();

    // * CExp ::= LogicalExp ([ < | <= | >= | > | == | != ] LogicalExp)?
    Exp *parseCExp();

    // * LogicalExp ::= OrExp ((&& | ||) OrExp)*
    Exp *parseLogicalExp();

    // * OrExp ::= XorExp (or XorExp)*
    Exp *parseOrExp();

    // * XorExp ::= AndExp (xor AndExp)*
    Exp *parseXorExp();

    // * AndExp ::= ShiftExp (and ShiftExp)*
    Exp *parseAndExp();

    // * ShiftExp ::= Exp (( shl | shr | ushr ) Exp)*
    Exp *parseShiftExp();

    // * Exp ::= Term (( + | - ) Term)*
    Exp *parseExpression();

    // * Term ::= Factor (( * | / | % ) Factor)*
    Exp *parseTerm();

    // ? PrefixOp

    /*
    * Factor ::= id
    *     | Num
    *     | Bool
    *     | (CExp)
    *     | PrefixOp Factor
    *     | id([ArgList])
    *     | id.("toByte" | "toShort" | "toInt" | "toLong" | "toUByte" | "toUShort" | "toUInt" | "toULong")()
    */
    Exp *parseFactor();
    
    // ? ArgList
    // ? Bool
    // ? Num
    // ? Digit

public:
    Parser(Scanner *scanner);

    // * Program ::= VarDecList FunDecList
    Program *parseProgram();

    // * VarDecList ::= (VarDec_1)*
    VarDecList *parseVarDecList();

    // * FunDecList ::= (FunDec)+
    FunDecList *parseFunDecList();

    // ? why the rules after this line should be public instead of private...?

    // * FunDec ::= fun id ([ParamDecList]) [: Type] {Body}
    FunDec *parseFunDec();

    // * Body ::= VarDecList StmList
    Body *parseBody();

    // ? ParamDecList

    /*
       * VarDec_1
       ? Type
       * VarDec_2
    */
    VarDec *parseVarDec();

    // * StmList ::= Stm [(; Stm)*]
    StatementList *parseStatementList();

    /*
    * Stm ::= id AugAssign CExp
    *   | id = CExp
    *   | println(CExp)
    *   | print(CExp)
    *   | if (CExp) {Body} [else {Body}]
    *   | for (id in CExp..CExp [step CExp]) {Body}
    *   | while (CExp) {Body}
    *   | return CExp
    */
    Stm *parseStatement();

    // ? AugAssign
};

#endif