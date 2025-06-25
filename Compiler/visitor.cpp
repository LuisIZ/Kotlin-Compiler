#include <iostream>
#include "exp.h"
#include "visitor.h"

using namespace std;

// new -------------------------------- Accept Visitors ------------------------------

int IdentifierExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int NumberExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int BoolExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int BinaryExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int PrefixExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int FCallExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int ConversionExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int StringExp::accept(Visitor *visitor)
{
    return visitor->visit(this); // TODO: ask professor about the class StringExp (our grammar does not have strings in Factor)
}

///////////////////////////////////////////////////////////////////////////////////

int AugmentedAssignStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int AssignStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int PrintLnStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int PrintStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int IfStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int ForStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int WhileStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int ReturnStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////

int StatementList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int VarDec::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int Body::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FunDec::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FunDecList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int VarDecList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int Program::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

// new -------------------------------- GenCode Visitors ------------------------------

