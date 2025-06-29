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

    // ! PrefixOp is going to be implemented in another rule in the parser

    // ! string implementation is just a formality but we are not going to use it... however, the compiler can scan and parse strings
    /*
    * Factor ::= id
    *     | Num
    *     | Bool
    !     | StringExp
    *     | (CExp)
    *     | PrefixOp Factor
    *     | id([ArgList])
    *     | id.("toInt" | "toLong" | "toUInt" | "toULong")()
    */
    Exp *parseFactor();

    // ! ArgList is going to be implemented in another rule in the parser
    // ! Bool is going to be implemented in another rule in the parser
    // ! Num is going to be implemented in another rule in the parser
    // ! Digit is going to be implemented in another rule in the parser

public:
    Parser(Scanner *scanner);

    // * Program ::= VarDecList FunDecList
    Program *parseProgram();

    // * VarDecList ::= (VarDec_1)*
    VarDecList *parseVarDecList();

    // * FunDecList ::= (FunDec)+
    FunDecList *parseFunDecList();

    // ! this are public because is more like the structure of the program... want to have access to the structure but respect the operations and result (private attributes...)

    // * FunDec ::= fun id ([ParamDecList]) [: Type] {Body}
    FunDec *parseFunDec();

    // * Body ::= VarDecList StmList
    Body *parseBody();

    // ! ParamDecList is going to be implemented in another rule in the parser

    /*
       * VarDec_1
       ! Type is going to be dealed in the visitors...
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

    // ! AugAssign is going to be implemented in another rule in the parser
};

#endif