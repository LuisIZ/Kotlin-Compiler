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
    return visitor->visit(this); // ! we are not going to use it really...
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

void GenCodeVisitor::generate(Program *program)
{
    program->accept(this);
}

// * Program ::= VarDecList FunDecList
void GenCodeVisitor::visit(Program *program)
{
    out << ".data\nprint_fmt: .string \"%ld \\n\"" << endl;
    program->vardecs->accept(this);

    for (auto &[var, _] : globalMemory)
    {
        out << var << ": .quad 0" << endl;
    }

    out << ".text\n";
    program->fundecs->accept(this);
    out << ".section .note.GNU-stack,\"\",@progbits" << endl;
}

// * VarDec_1 ::= var id: Type [(; VarDec_2)*] | | val id: Type [(; VarDec_2)*]
// * VarDec_2 ::= var id: Type | val id : Type not necessary to create a class
void GenCodeVisitor::visit(VarDec *stm)
{
    for (auto var : stm->vars)
    {
        if (!enviromentFunction)
        {
            globalMemory[var] = true;
        }
        else
        {
            memory[var] = offset;
            offset -= 8;
        }
    }
}

// * VarDecList ::= (VarDec_1)*
void GenCodeVisitor::visit(VarDecList *stm)
{
    for (auto dec : stm->vardecs)
        dec->accept(this);
}

// * Factor ::= Num
int GenCodeVisitor::visit(NumberExp *exp)
{
    switch (exp->type)
    {
    case INT:
        out << " movl $" << exp->value << ", " << "%eax";
        break;
    case UINT:
        out << " movl $" << exp->value << ", " << "%eax";
        break;
    case LONG:
        out << " movq $" << exp->value << ", " << "%rax";
        break;
    case ULONG:
        out << " movq $" << exp->value << ", " << "%rax";
        break;
    }
    out << endl;
    return 0;
}

// * Factor ::= id
int GenCodeVisitor::visit(IdentifierExp *exp)
{
    if (globalMemory.count(exp->name))
        out << " movq " << exp->name << "(%rip), %rax" << endl;
    else
        out << " movq " << memory[exp->name] << "(%rbp), %rax" << endl;
    return 0;
}

// * Factor ::= (CExp)
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
int GenCodeVisitor::visit(BinaryExp *exp)
{
    exp->left->accept(this);
    out << " pushq %rax\n";
    exp->right->accept(this);
    out << " movq %rax, %rcx\n popq %rax\n";

    switch (exp->op)
    {
    case PLUS_OP:
        out << " addq %rcx, %rax\n";
        break;
    case MINUS_OP:
        out << " subq %rcx, %rax\n";
        break;
    case MUL_OP:
        out << " imulq %rcx, %rax\n";
        break;
    case DIV_OP:
        out << " cqto\n"
            << " idivq %rcx\n";
        break;
    case MOD_OP:
        out << " cqto\n"
            << " idivq %rcx\n"
            << " movq %rdx, %rax\n";
        break;
    case LE_OP:
        out << " cmpq %rcx, %rax\n"
            << " movq $0, %rax\n"
            << " setle %al\n"
            << " movzbq %al, %rax\n";
        break;
    case LT_OP:
        out << " cmpq %rcx, %rax\n"
            << " movq $0, %rax\n"
            << " setl %al\n"
            << " movzbq %al, %rax\n";
        break;
    case GT_OP:
        out << " cmpq %rcx, %rax\n"
            << " movq $0, %rax\n"
            << " setg %al\n"
            << " movzbq %al, %rax\n";
        break;
    case GE_OP:
        out << " cmpq %rcx, %rax\n"
            << " movq $0, %rax\n"
            << " setge %al\n"
            << " movzbq %al, %rax\n";
        break;
    case EQ_OP:
        out << " cmpq %rcx, %rax\n"
            << " movq $0, %rax\n"
            << " sete %al\n"
            << " movzbq %al, %rax\n";
        break;
    case DIFF_OP:
        out << " cmpq %rcx, %rax\n"
            << " movq $0, %rax\n"
            << " setne %al\n"
            << " movzbq %al, %rax\n";
        break;
    case LOG_AND_OP:
        out << " andq %rcx, %rax\n";
        break;
    case LOG_OR_OP:
        out << " orq %rcx, %rax\n";
        break;
    case BW_AND_OP:
        out << " andq %rcx, %rax\n";
        break;
    case BW_OR_OP:
        out << " orq %rcx, %rax\n";
        break;
    case BW_XOR_OP:
        out << " xorq %rcx, %rax\n";
        break;
    case BW_SHL_OP:
        out << " shlq %cl, %rax\n";
        break;
    case BW_SHR_OP:
        out << " sarq %cl, %rax\n";
        break;
    case BW_USHR_OP:
        out << " shrq %cl, %rax\n";
        break;
    default:
        break;
    }
    return 0;
}

// * Stm ::= id = CExp
void GenCodeVisitor::visit(AssignStatement *stm)
{
    stm->rhs->accept(this);
    if (globalMemory.count(stm->id))
        out << " movq %rax, " << stm->id << "(%rip)" << endl;
    else
        out << " movq %rax, " << memory[stm->id] << "(%rbp)" << endl;
}

// * Stm ::= print(CExp)
void GenCodeVisitor::visit(PrintStatement *stm)
{
    stm->e->accept(this);
    out << " movq %rax, %rsi\n"
           " leaq print_fmt(%rip), %rdi\n"
           " movq $0, %rax\n"
           " call printf@PLT\n";
}

// * FunDecList ::= (FunDec)+
void GenCodeVisitor::visit(FunDecList *f)
{
    for (auto dec : f->Fundecs)
        dec->accept(this);
}

// * StmList ::= Stm [([;] Stm)*]
void GenCodeVisitor::visit(StatementList *stm)
{
    for (auto s : stm->stms)
    {
        s->accept(this);
    }
}

// * Body ::= VarDecList StmList
void GenCodeVisitor::visit(Body *b)
{
    b->vardecs->accept(this);
    b->slist->accept(this);
}

// * Stm ::= if (CExp) {Body} [else {Body}]
void GenCodeVisitor::visit(IfStatement *stm)
{
    int label = countLabel++;
    stm->condition->accept(this);
    out << " cmpq $0, %rax" << endl;
    out << " je else_" << label << endl;
    stm->then->accept(this);
    out << " jmp endif_" << label << endl;
    out << " else_" << label << ":" << endl;
    if (stm->els)
        stm->els->accept(this);
    out << "endif_" << label << ":" << endl;
}

// * Stm ::= while (CExp) {Body}
void GenCodeVisitor::visit(WhileStatement *stm)
{
    int label = countLabel++;
    out << "while_" << label << ":" << endl;
    stm->condition->accept(this);
    out << " cmpq $0, %rax" << endl;
    out << " je endwhile_" << label << endl;
    stm->b->accept(this);
    out << " jmp while_" << label << endl;
    out << "endwhile_" << label << ":" << endl;
}

// * Factor ::= Bool
int GenCodeVisitor::visit(BoolExp *exp)
{
    out << " movq $" << exp->value << ", %rax" << endl;
    return 0;
}

// * Stm ::= return CExp
void GenCodeVisitor::visit(ReturnStatement *stm)
{
    stm->e->accept(this);
    out << " jmp .end_" << functionName << endl;
}

// * FunDec ::= fun id ([ParamDecList]) [: Type] {Body}
void GenCodeVisitor::visit(FunDec *f)
{
    enviromentFunction = true;
    functionName = f->id; // ! update function name
    memory.clear();
    offset = -8;

    // ! map (offset) local variables
    for (auto var : f->b->vardecs->vardecs)
    {
        var->accept(this);
    }

    // ! map (offset) parameters
    for (auto &param : f->params)
    {
        memory[param] = offset;
        offset -= 8;
    }

    int frameSize = (-offset - 8);
    if (frameSize & 15) // ! 16 bytes
    {
        frameSize += 8;
    }

    // ! prologue (reserve space in stack = function frame)
    out << ".globl " << f->id << '\n'
        << f->id << ":\n"
        << " pushq %rbp\n"
        << " movq %rsp, %rbp\n";
    if (frameSize)
    {
        out << " subq $" << frameSize << ", %rsp" << endl;
    }

    // ! copy arguments to funtion frame
    const char *argReg[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    for (size_t i = 0; i < f->params.size(); ++i)
    {
        out << " movq " << argReg[i] << ", "
            << memory[f->params[i]] << "(%rbp)\n";
    }

    // ! function body
    f->b->slist->accept(this);

    // ! epilogue
    out << ".end_" << f->id << ":\n"
        << " leave\n"
        << " ret\n";

    enviromentFunction = false;
}

// * Factor ::= id([ArgList])
int GenCodeVisitor::visit(FCallExp *exp)
{
    vector<std::string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int size = exp->arglist.size();

    int i = 0;
    for (auto arg : exp->arglist)
    {
        if (i >= argRegs.size())
            break;
        arg->accept(this);
        out << " movq %rax, " << argRegs[i] << endl; // ! make sure we are working with 64 bits in case some argument is long type
        i++;
    }

    out << "call " << exp->id << endl;
    return 0;
}

// * Factor ::= PrefixOp Factor
/*
TODO:

! PrefixOp ::= +
*            | -
*            | !
!            | ++
!            | --
!            | inv
*/
int GenCodeVisitor::visit(PrefixExp *exp)
{
    exp->right->accept(this);

    switch (exp->op)
    {
    case MINUS_OP:
        out << " negq %rax" << endl;
        break;
    case NOT_OP:
        out << " cmpq $0, %rax" << endl
            << " sete %al" << endl
            << " movzbq %al, %rax" << endl;
        break;
    }
    return 0;
}

// * Factor ::= id.("toInt" | "toLong" | "toUInt" | "toULong")()
int GenCodeVisitor::visit(ConversionExp *exp)
{
    if (globalMemory.count(exp->id))
    {
        out << " movq " << exp->id << "(%rip), %rax" << endl;
    }
    else
    {
        out << " movq " << memory[exp->id] << "(%rbp), %rax" << endl;
    }

    switch (exp->convType)
    {
    case TO_INT_FUN: // ! change to 32 bit (with sign)
        out << " movslq %eax, %rax" << endl;
        break;
    case TO_U_INT_FUN: // ! change to 32 bit (without sign)
        out << " movl %eax, %eax" << endl;
        break;
    case TO_LONG_FUN: // ! already working with 64 bits
        break;
    case TO_U_LONG_FUN:
        break;
    }

    return 0;
}

// * Stm ::= id AugAssign CExp
// * AugAssign ::= += | -= | *= | /= | %=
void GenCodeVisitor::visit(AugmentedAssignStatement *stm)
{
    // ! load variable
    if (globalMemory.count(stm->id))
    {
        out << " movq " << stm->id << "(%rip), %rax" << endl;
    }
    else
    {
        out << " movq " << memory[stm->id] << "(%rbp), %rax" << endl;
    }

    out << " pushq %rax" << endl;
    stm->rhs->accept(this);
    out << " movq %rax, %rcx" << endl;
    out << " popq %rax" << endl;

    // ! choose augmented assign operator
    switch (stm->op)
    {
    case AA_PLUS_OP:
        out << " addq %rcx, %rax" << endl;
        break;
    case AA_MINUS_OP:
        out << " subq %rcx, %rax" << endl;
        break;
    case AA_MUL_OP:
        out << " imulq %rcx, %rax" << endl;
        break;
    case AA_DIV_OP:
        out << " cqto" << endl;
        out << " idivq %rcx" << endl;
        break;
    case AA_MOD_OP:
        out << " cqto" << endl;
        out << " idivq %rcx" << endl;
        out << " movq %rdx, %rax" << endl;
        break;
    }

    // ! save result
    if (globalMemory.count(stm->id))
    {
        out << " movq %rax, " << stm->id << "(%rip)" << endl;
    }
    else
    {
        out << " movq %rax, " << memory[stm->id] << "(%rbp)" << endl;
    }
}

// * Stm ::= println(CExp)
void GenCodeVisitor::visit(PrintLnStatement *stm)
{
    stm->e->accept(this);
    out << " movq %rax, %rsi" << endl
        << " leaq print_fmt(%rip), %rdi" << endl
        << " movq $0, %rax" << endl
        << " call printf@PLT" << endl;
}

// * Stm ::= for (id in CExp..CExp [step CExp]) {Body}
void GenCodeVisitor::visit(ForStatement *stm)
{
    const string &it = stm->id;
    int label = countLabel++;

    // ! reserve local slot only if iterator isn't a global variable
    if (!globalMemory.count(it))
    {
        memory[stm->id] = offset;
        offset -= 8;
        out << " subq $8, %rsp\n";
    }

    // ! start
    AssignStatement init(it, stm->start);
    init.accept(this);

    out << "for_" << label << ":\n";

    // ! condition (start <= end)
    BinaryExp condition(new IdentifierExp(it), stm->end, LE_OP);
    condition.accept(this);
    out << " cmpq $0, %rax\n"
        << " je endfor_" << label << "\n";

    // ! for body
    stm->body->accept(this);

    // ! increment iterator
    // ! i = i + (step ? step : 1) -> Step exist?
    if (globalMemory.count(it))
    {
        out << " movq " << it << "(%rip), %rax\n";
    }
    else
    {
        out << " movq " << memory[it] << "(%rbp), %rax\n";
    }

    out << " pushq %rax\n"; // ! save iterator

    if (stm->step)
    {
        stm->step->accept(this); // ! rax = step
    }
    else
    {
        out << " movq $1, %rax\n"; // ! by default iterator = iterator + 1
    }

    out << " movq %rax, %rcx\n"  // ! rcx = step
        << " popq %rax\n"        // ! rax = i
        << " addq %rcx, %rax\n"; // ! i += step

    if (globalMemory.count(it))
    {
        out << " movq %rax, " << it << "(%rip)\n";
    }
    else
    {
        out << " movq %rax, " << memory[it] << "(%rbp)\n";
    }

    // ! finish or continue the for loop
    out << " jmp for_" << label << "\n"
        << "endfor_" << label << ":\n";
}

// ! remember: for this project we do not work with strings... its just a formality xD
int GenCodeVisitor::visit(StringExp *exp)
{
    return 0;
}