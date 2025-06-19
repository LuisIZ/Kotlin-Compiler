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

enum PrefixOp
{
    // ? how do I implement + and -
    // * PrefixOp ::= + | - | ! | ++ | -- | inv 
    NOT_OP,
    PRE_INC_OP,
    PRE_DEC_OP,
    INV_OP
};

class Exp
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
};

///////////////////////////////////////////////////////////////////////////////////

// * Stm ::=
class Stm
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Stm() = 0;
};

// * Stm ::= id AugAssign CExp
class AugmentedAssignStatement : public Stm // ? Is it necessary or I could only use AssignStatement
{
public:
    std::string id;
    Exp *rhs;
    AugmentedAssignStatement(std::string id, Exp *e);
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
    Body *els;
    IfStatement(Exp *condition, Body *then, Body *els);
    int accept(Visitor *visitor);
    ~IfStatement();
};

// ? How could I implement the for stm taking into account ForRangeExp ::=  CExp..CExp [step CExp]
// * Stm ::= for (id in ForRangeExp) {Body}

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
    Exp *e;
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

// ? Is VarDec_2 ::= var id: Type | val id : Type not necessary to create a class

// ? Is Type ::= id not necessary to create a class

// * VarDec_1 ::= var id: Type [(; VarDec_2)*] | | val id: Type [(; VarDec_2)*]
class VarDec
{
public:
    string type;
    list<string> vars;
    VarDec(string type, list<string> vars);
    int accept(Visitor *visitor);
    ~VarDec();
};

// ? Is ParamDecList ::= id: Type (, id: Type)* not necessary to create a class

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
    int accept(Visitor *visitor)
};

#endif