#ifndef EXP_H
#define EXP_H

#include <string>
#include <unordered_map>
#include <list>
#include "visitor.h"

using namespace std;

enum BinaryOp
{
    // * CExp ::= LogicalExp ([ < | <= | >= | > | == | != ] LogicalExp)?
    LT_OP,
    LE_OP,
    GT_OP,
    GE_OP,
    EQ_OP,
    DIFF_OP,

    // * LogicalExp ::= OrExp ((&& | ||) OrExp)*
    LOG_AND_OP,
    LOG_OR_OP,

    // * OrExp ::= XorExp (or XorExp)*
    BW_OR_OP,

    // * XorExp ::= AndExp (xor AndExp)*
    BW_XOR_OP,

    // * AndExp ::= ShiftExp (and ShiftExp)*
    BW_AND_OP,

    // * ShiftExp ::= Exp (( shl | shr | ushr ) Exp)*
    BW_SHL_OP,
    BW_SHR_OP,
    BW_USHR_OP,

    // * Exp ::= Term (( + | - ) Term)*
    PLUS_OP,
    MINUS_OP,

    // * Term ::= Factor (( * | / | % ) Factor)*
    MUL_OP,
    DIV_OP,
    MOD_OP
};

// * PrefixOp ::= + | - | ! | ++ | -- | inv
enum PrefixOp
{
    POS_OP, // +1
    NEG_OP, // -1
    NOT_OP,
    PRE_INC_OP,
    PRE_DEC_OP,
    INV_OP
};

// * AugAssign ::= += | -= | *= | /= | %=
enum AugmentedOp
{
    AA_PLUS_OP,
    AA_MINUS_OP,
    AA_MUL_OP,
    AA_DIV_OP,
    AA_MOD_OP
};

// * Factor ::= id.("toByte" | "toShort" | "toInt" | "toLong" | "toUByte" | "toUShort" | "toUInt" | "toULong")()
enum ConversionTypeFun
{
    TO_BYTE_FUN,
    TO_SHORT_FUN,
    TO_INT_FUN,
    TO_LONG_FUN,
    TO_U_BYTE_FUN,
    TO_U_SHORT_FUN,
    TO_U_INT_FUN,
    TO_U_LONG_FUN
};

// * Num ::= Digit+ ([ u | U ] [ l | L ]? | [ l | L ] [ u | U ]?)
enum numType
{
    INT,
    UINT,
    LONG,
    ULONG
};

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
class Exp
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Exp() = 0;
    static string binOpToString(BinaryOp op);
    static string prefixOpToString(PrefixOp op);
    static string augOpToString(AugmentedOp op);
    static string convFunToString(ConversionTypeFun op); // ! I need to convert also the functions...
};

// * Factor ::= id
class IdentifierExp : public Exp
{
public:
    std::string name;
    IdentifierExp(const std::string &n);
    int accept(Visitor *visitor);
    ~IdentifierExp();
};

// TODO: ask professor...
// * Factor ::= Num
class NumberExp : public Exp
{
public:
    int value;
    numType type;
    NumberExp(int v, numType t); // ! I need to recognize somehow the type for the codegen...
    int accept(Visitor *visitor);
    ~NumberExp();
};

// * Factor ::= Bool
class BoolExp : public Exp
{
public:
    bool value;
    BoolExp(bool v);
    int accept(Visitor *visitor);
    ~BoolExp();
};

// * Factor ::= (CExp)
class BinaryExp : public Exp
{
public:
    Exp *left, *right;
    BinaryOp op;
    BinaryExp(Exp *l, Exp *r, BinaryOp op);
    int accept(Visitor *visitor);
    ~BinaryExp();
};

// * Factor ::= PrefixOp Factor
class PrefixExp : public Exp
{
public:
    Exp *right;
    PrefixOp op;
    PrefixExp(Exp *r, PrefixOp op);
    int accept(Visitor *visitor);
    ~PrefixExp();
};

// * Factor ::= id([ArgList])
class FCallExp : public Exp
{
public:
    // * ArgList ::= CExp (, CExp)*
    string id;
    list<Exp *> arglist;

    FCallExp() {};
    ~FCallExp() {};
    int accept(Visitor *visitor);
};

// * Factor ::= id.("toByte" | "toShort" | "toInt" | "toLong" | "toUByte" | "toUShort" | "toUInt" | "toULong")()
class ConversionExp : public Exp
{
public:
    string id;
    ConversionTypeFun convType;
    ConversionExp(string id, ConversionTypeFun convType);
    int accept(Visitor *visitor);
    ~ConversionExp();
};

///////////////////////////////////////////////////////////////////////////////////

// TODO: ask professor about the class StringExp (our grammar does not have strings in Factor)
class StringExp : public Exp
{
public:
    string value;
    StringExp(string v);
    int accept(Visitor *visitor);
    ~StringExp();
};

///////////////////////////////////////////////////////////////////////////////////

class Stm
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Stm() = 0;
};

// * Stm ::= id AugAssign CExp
class AugmentedAssignStatement : public Stm
{
public:
    std::string id;
    Exp *rhs;
    AugmentedOp op;
    AugmentedAssignStatement(std::string id, AugmentedOp op, Exp *rhs);
    int accept(Visitor *visitor);
    ~AugmentedAssignStatement();
};

// * Stm ::= id = CExp
class AssignStatement : public Stm
{
public:
    std::string id;
    Exp *rhs;
    AssignStatement(std::string id, Exp *e);
    int accept(Visitor *visitor);
    ~AssignStatement();
};

// * Stm ::= println(CExp)
class PrintLnStatement : public Stm
{
public:
    Exp *e;
    PrintLnStatement(Exp *e);
    int accept(Visitor *visitor);
    ~PrintLnStatement();
};

// * Stm ::= print(CExp)
class PrintStatement : public Stm
{
public:
    Exp *e;
    PrintStatement(Exp *e);
    int accept(Visitor *visitor);
    ~PrintStatement();
};

// * Stm ::= if (CExp) {Body} [else {Body}]
class IfStatement : public Stm
{
public:
    Exp *condition;
    Body *then;
    Body *els; // ! is optional
    IfStatement(Exp *condition, Body *then, Body *els = nullptr);
    int accept(Visitor *visitor);
    ~IfStatement();
};

// * Stm ::= for (id in CExp..CExp [step CExp]) {Body}
class ForStatement : public Stm
{
public:
    string id;
    Body *body;

    Exp *start;
    Exp *end;
    Exp *step;

    ForStatement(string id, Body *b, Exp *s, Exp *e, Exp *st = nullptr);
    int accept(Visitor *visitor);
    ~ForStatement();
};

// * Stm ::= while (CExp) {Body}
class WhileStatement : public Stm
{
public:
    Exp *condition;
    Body *b;
    WhileStatement(Exp *condition, Body *b);
    int accept(Visitor *visitor);
    ~WhileStatement();
};

// * Stm ::= return CExp
class ReturnStatement : public Stm
{
public:
    Exp *e; // ? Should I change it to nullptr because a function could return nothing
    ReturnStatement() {};
    ~ReturnStatement() {};
    int accept(Visitor *visitor);
};

///////////////////////////////////////////////////////////////////////////////////

// * StmList ::= Stm [(; Stm)*]
class StatementList
{
public:
    list<Stm *> stms;
    StatementList();
    void add(Stm *stm);
    int accept(Visitor *visitor);
    ~StatementList();
};

// * VarDec_1 ::= var id: Type [(; VarDec_2)*] | | val id: Type [(; VarDec_2)*]
// * VarDec_2 ::= var id: Type | val id : Type not necessary to create a class
class VarDec
{
public:
    string type;
    list<string> vars;
    VarDec(string type, list<string> vars);
    int accept(Visitor *visitor);
    ~VarDec();
};

// * Body ::= VarDecList StmList
class Body
{
public:
    VarDecList *vardecs;
    StatementList *slist;
    int accept(Visitor *visitor);
    Body(VarDecList *vardecs, StatementList *stms);
    ~Body();
};

// * FunDec ::= fun id ([ParamDecList]) [: Type] {Body}
class FunDec
{
public:
    string id;
    string type;

    // * ParamDecList ::= id: Type (, id: Type)* not necessary to create a class
    vector<string> params;
    list<string> params_types;

    Body *b;
    FunDec() {};
    ~FunDec() {};
    int accept(Visitor *visitor);
};

// * FunDecList ::= (FunDec)+
class FunDecList
{
public:
    list<FunDec *> Fundecs;
    void add(FunDec *fundec)
    {
        Fundecs.push_back(fundec);
    };
    int accept(Visitor *visitor);
    FunDecList() {};
    ~FunDecList() {};
};

// * VarDecList ::= (VarDec_1)*
class VarDecList
{
public:
    list<VarDec *> vardecs;
    VarDecList();
    void add(VarDec *vardec);
    int accept(Visitor *visitor);
    ~VarDecList();
};

// * Program ::= VarDecList FunDecList
class Program
{
public:
    VarDecList *vardecs;
    FunDecList *fundecs;
    Program() {};
    ~Program() {};
    int accept(Visitor *visitor);
};

#endif