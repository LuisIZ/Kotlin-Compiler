#include "exp.h"
#include <iostream>
#include <algorithm>

using namespace std;

/*
 * CExp ::= LogicalExp ([ < | <= | >= | > | == | != ] LogicalExp)?
 * LogicalExp ::= OrExp ((&& | ||) OrExp)*
 * OrExp ::= XorExp (or XorExp)*
 * XorExp ::= AndExp (xor AndExp)*
 * AndExp ::= ShiftExp (and ShiftExp)*
 * ShiftExp ::= Exp (( shl | shr | ushr ) Exp)*
 * Exp ::= Term (( + | - ) Term)*
 * Term ::= Factor (( * | / | % ) Factor)*
 */
Exp::~Exp() {}
string Exp::binOpToString(BinaryOp op)
{
    string c;
    switch (op)
    {
    // * CExp ::= LogicalExp ([ < | <= | >= | > | == | != ] LogicalExp)?
    case LT_OP:
        c = "<";
        break;
    case LE_OP:
        c = "<=";
        break;
    case GT_OP:
        c = ">";
        break;
    case GE_OP:
        c = ">=";
        break;
    case EQ_OP:
        c = "==";
        break;
    case DIFF_OP:
        c = "!=";
        break;

    // * LogicalExp ::= OrExp ((&& | ||) OrExp)*
    case LOG_AND_OP:
        c = "&&";
        break;
    case LOG_OR_OP:
        c = "||";
        break;

    // * OrExp ::= XorExp (or XorExp)*
    case BW_OR_OP:
        c = "or";
        break;

    // * XorExp ::= AndExp (xor AndExp)*
    case BW_XOR_OP:
        c = "xor";
        break;

    // * AndExp ::= ShiftExp (and ShiftExp)*
    case BW_AND_OP:
        c = "and";
        break;

    // * ShiftExp ::= Exp (( shl | shr | ushr ) Exp)*
    case BW_SHL_OP:
        c = "shl";
        break;
    case BW_SHR_OP:
        c = "shr";
        break;
    case BW_USHR_OP:
        c = "ushr";
        break;

    // * Exp ::= Term (( + | - ) Term)*
    case PLUS_OP:
        c = "+";
        break;
    case MINUS_OP:
        c = "-";
        break;

    // * Term ::= Factor (( * | / | % ) Factor)*
    case MUL_OP:
        c = "*";
        break;
    case DIV_OP:
        c = "/";
        break;
    case MOD_OP:
        c = "%";
        break;

    default:
        cout
            << "Error: unidentified binary operator to convert to string"
            << endl;
        exit(1);
        break; // ? Is it necessary, I mean, I already exit the program with exit(1)
    }
    return c;
}

string Exp::prefixOpToString(PrefixOp op)
{
    string c;
    // * PrefixOp ::= + | - | ! | ++ | -- | inv
    switch (op)
    {
    case POS_OP:
        c = "+";
        break;
    case NEG_OP:
        c = "-";
        break;
    case NOT_OP:
        c = "!";
        break;
    case PRE_INC_OP:
        c = "++";
        break;
    case PRE_DEC_OP:
        c = "--";
        break;
    case INV_OP:
        c = "inv";
        break;

    default:
        cout
            << "Error: unidentified prefix operator to convert to string"
            << endl;
        exit(1);
        break;
    }
    return c;
}

string Exp::augOpToString(AugmentedOp op)
{
    string c;
    // * AugAssign ::= += | -= | *= | /= | %=
    switch (op)
    {
    case AA_PLUS_OP:
        c = "+=";
        break;
    case AA_MINUS_OP:
        c = "-=";
        break;
    case AA_MUL_OP:
        c = "*=";
        break;
    case AA_DIV_OP:
        c = "/=";
        break;
    case AA_MOD_OP:
        c = "%=";
        break;

    default:
        cout
            << "Error: unidentified augmented assign operator to convert to string"
            << endl;
        exit(1);
        break;
    }
    return c;
}

string Exp::convFunToString(ConversionTypeFun op)
{
    string c;
    // * Factor ::= id.("toByte" | "toShort" | "toInt" | "toLong" | "toUByte" | "toUShort" | "toUInt" | "toULong")()
    switch (op)
    {
    case TO_BYTE_FUN:
        c = "toByte";
        break;
    case TO_SHORT_FUN:
        c = "toShort";
        break;
    case TO_INT_FUN:
        c = "toInt";
        break;
    case TO_LONG_FUN:
        c = "toLong";
        break;
    case TO_U_BYTE_FUN:
        c = "toUByte";
        break;
    case TO_U_SHORT_FUN:
        c = "toUShort";
        break;
    case TO_U_INT_FUN:
        c = "toUInt";
        break;
    case TO_U_LONG_FUN:
        c = "toULong";
        break;

    default:
        cout
            << "Error: unidentified conversion type function to convert to string"
            << endl;
        exit(1);
        break;
    }
    return c;
}

// * ForRangeExp ::=  CExp..CExp [step CExp]
ForRangeExp::ForRangeExp(Exp *s, Exp *e, Exp *st = nullptr) : start(s), end(e), step(st) {}
ForRangeExp::~ForRangeExp()
{
    delete start;
    delete end;
    delete step;
}

// * Factor ::= id
IdentifierExp::IdentifierExp(const std::string &n) : name(n) {}
IdentifierExp::~IdentifierExp() {}

// * Factor ::= Num
NumberExp::NumberExp(int v) : value(v) {}
NumberExp::~NumberExp() {}

// * Factor ::= Bool
BoolExp::BoolExp(bool v) : value(v) {}
BoolExp::~BoolExp() {}

// * Factor ::= (CExp)
BinaryExp::BinaryExp(Exp *l, Exp *r, BinaryOp op) : left(l), right(r), op(op) {}
BinaryExp::~BinaryExp()
{
    delete left;
    delete right;
}

// * Factor ::= PrefixOp Factor
PrefixExp::PrefixExp(Exp *r, PrefixOp op) : right(r), op(op) {}
PrefixExp::~PrefixExp()
{
    delete right;
}

// * Factor ::= id([ArgList]) is already implemented in exp.h in FCallExp

// * Factor ::= id.("toByte" | "toShort" | "toInt" | "toLong" | "toUByte" | "toUShort" | "toUInt" | "toULong")()
ConversionExp::ConversionExp(string id, ConversionTypeFun convType) : id(id), convType(convType) {}
ConversionExp::~ConversionExp() {}

///////////////////////////////////////////////////////////////////////////////////

// TODO: ask professor about the class StringExp (our grammar does not have strings in Factor)
StringExp::StringExp(string v) : value(v) {}
StringExp::~StringExp() {}

///////////////////////////////////////////////////////////////////////////////////

Stm::~Stm() {}

// * Stm ::= id AugAssign CExp
AugmentedAssignStatement::AugmentedAssignStatement(std::string id, AugmentedOp op, Exp *rhs) : id(id), rhs(rhs), op(op) {}
AugmentedAssignStatement::~AugmentedAssignStatement()
{
    delete rhs;
}

// * Stm ::= id = CExp
AssignStatement::AssignStatement(std::string id, Exp *e) : id(id), rhs(e) {}
AssignStatement::~AssignStatement()
{
    delete rhs;
}

// * Stm ::= println(CExp)
PrintLnStatement::PrintLnStatement(Exp* e) : e(e) {}
PrintLnStatement::~PrintLnStatement()
{
    delete e;
}

// * Stm ::= print(CExp)
PrintStatement::PrintStatement(Exp *e) : e(e) {}
PrintStatement::~PrintStatement()
{
    delete e;
}

// * Stm ::= if (CExp) {Body} [else {Body}]
IfStatement::IfStatement(Exp *condition, Body *then, Body *els = nullptr) : condition(condition), then(then), els(els) {}
IfStatement::~IfStatement()
{
    delete condition;
    delete then;
    delete els;
}

// * Stm ::= for (id in ForRangeExp) {Body}
ForStatement::ForStatement(string id, ForRangeExp *r, Body *b) : id(id), range(r), body(b) {}
ForStatement::~ForStatement()
{
    delete range;
    delete body;
}

// * Stm ::= while (CExp) {Body}
WhileStatement::WhileStatement(Exp *condition, Body *b) : condition(condition), b(b) {}
WhileStatement::~WhileStatement()
{
    delete condition;
    delete b;
}

// * Stm ::= return CExp is already implemented in exp.h with ReturnStatement

///////////////////////////////////////////////////////////////////////////////////

// * StmList ::= Stm [(; Stm)*]
StatementList::StatementList() : stms() {}
void StatementList::add(Stm *s) {
    stms.push_back(s);
}
StatementList::~StatementList()
{
    for (auto s : stms)
    {
        delete s;
    }
}

// * VarDec_1 ::= var id: Type [(; VarDec_2)*] | | val id: Type [(; VarDec_2)*]
// * VarDec_2 ::= var id: Type | val id : Type not necessary to create a class
VarDec::VarDec(string type, list<string> vars) : type(type), vars(vars) {}
VarDec::~VarDec() {}

// * Body ::= VarDecList StmList
Body::Body(VarDecList *vardecs, StatementList *stms) : vardecs(vardecs), slist(stms) {}
Body::~Body()
{
    delete vardecs;
    delete slist;
}

// * FunDec ::= fun id ([ParamDecList]) [: Type] {Body} is already implemented in exp.h with FunDec

// * FunDecList ::= (FunDec)+ is already implemented in exp.h with FunDecList

// * VarDecList ::= (VarDec_1)*
VarDecList::VarDecList() : vardecs() {}
void VarDecList::add(VarDec *v)
{
    vardecs.push_back(v);
}
VarDecList::~VarDecList()
{
    for (auto v : vardecs)
    {
        delete v;
    }
}

// * Program ::= VarDecList FunDecList is already implemented in exp.h with Program