#ifndef VISITOR_H
#define VISITOR_H
#include "exp.h"
#include <list>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class IdentifierExp;
class NumberExp;
class BoolExp;
class BinaryExp;
class PrefixExp;
class FCallExp;
class ConversionExp;
class StringExp; // ! we are not going to use it really...

///////////////////////////////////////////////////////////////////////////////////

class AugmentedAssignStatement;
class AssignStatement;
class PrintLnStatement;
class PrintStatement;
class IfStatement;
class ForStatement;
class WhileStatement;
class ReturnStatement;

///////////////////////////////////////////////////////////////////////////////////

class StatementList;
class VarDec;
class Body;
class FunDec;
class FunDecList;
class VarDecList;
class Program;

class Visitor
{
public:
    virtual int visit(IdentifierExp *exp) = 0;
    virtual int visit(NumberExp *exp) = 0;
    virtual int visit(BoolExp *exp) = 0;
    virtual int visit(BinaryExp *exp) = 0;
    virtual int visit(PrefixExp *exp) = 0;
    virtual int visit(FCallExp *exp) = 0;
    virtual int visit(ConversionExp *exp) = 0;
    virtual int visit(StringExp *exp) = 0; // ! we are not going to use it really...

    ///////////////////////////////////////////////////////////////////////////////////

    virtual void visit(AugmentedAssignStatement *stm) = 0;
    virtual void visit(AssignStatement *stm) = 0;
    virtual void visit(PrintLnStatement *stm) = 0;
    virtual void visit(PrintStatement *stm) = 0;
    virtual void visit(IfStatement *stm) = 0;
    virtual void visit(ForStatement *stm) = 0;
    virtual void visit(WhileStatement *stm) = 0;
    virtual void visit(ReturnStatement *stm) = 0;

    ///////////////////////////////////////////////////////////////////////////////////

    virtual void visit(StatementList *stm) = 0;
    virtual void visit(VarDec *stm) = 0;
    virtual void visit(Body *b) = 0;
    virtual void visit(FunDec *f) = 0;
    virtual void visit(FunDecList *f) = 0;
    virtual void visit(VarDecList *stm) = 0;
    virtual void visit(Program *p) = 0;
};

class GenCodeVisitor : public Visitor
{
private:
    std::ostream &out;

public:
    GenCodeVisitor(std::ostream &out) : out(out) {}
    void generate(Program *program);

    unordered_map<string, int> memory;
    unordered_map<string, bool> globalMemory;

    int offset = -8;

    int countLabel = 0; // ! for nested WhileStatement and IfStatement

    bool enviromentFunction = false;
    string funtionName;

    ///////////////////////////////////////////////////////////////////////////////////

    int visit(IdentifierExp *exp) override;
    int visit(NumberExp *exp) override;
    int visit(BoolExp *exp) override;
    int visit(BinaryExp *exp) override;
    int visit(PrefixExp *exp) override;
    int visit(FCallExp *exp) override;
    int visit(ConversionExp *exp) override;
    int visit(StringExp *exp) override; // ! we are not going to use it really...

    ///////////////////////////////////////////////////////////////////////////////////

    void visit(AugmentedAssignStatement *stm) override;
    void visit(AssignStatement *stm) override;
    void visit(PrintLnStatement *stm) override;
    void visit(PrintStatement *stm) override;
    void visit(IfStatement *stm) override;
    void visit(ForStatement *stm) override;
    void visit(WhileStatement *stm) override;
    void visit(ReturnStatement *stm) override;

    ///////////////////////////////////////////////////////////////////////////////////

    void visit(StatementList *stm) override;
    void visit(VarDec *stm) override;
    void visit(Body *b) override;
    void visit(FunDec *f) override;
    void visit(FunDecList *f) override;
    void visit(VarDecList *stm) override;
    void visit(Program *p) override;
};

#endif