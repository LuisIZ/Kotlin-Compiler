#include <iostream>
#include <stdexcept>
#include <string>
#include <climits>
#include "token.h"
#include "scanner.h"
#include "exp.h"
#include "parser.h"

using namespace std;

bool Parser::match(Token::Type ttype)
{
    if (check(ttype))
    {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype)
{
    if (isAtEnd())
        return false;
    return current->type == ttype;
}

bool Parser::advance()
{
    if (!isAtEnd())
    {
        Token *temp = current;
        if (previous)
            delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR))
        {
            cout << "Error: not recognized character " << current->text << " during parsing." << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd()
{
    return (current->type == Token::END);
}

///////////////////////////////////////////////////////////////////////////////////

Parser::Parser(Scanner *sc) : scanner(sc)
{
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR)
    {
        cout << "Error: The first token " << current->text << " when parsing is not correct." << endl;
        exit(1);
    }
}

// * Program ::= VarDecList FunDecList
Program *Parser::parseProgram()
{
    Program *p = new Program();
    p->vardecs = parseVarDecList();
    p->fundecs = parseFunDecList();
    return p;
}

// * VarDecList ::= (VarDec_1)*
VarDecList *Parser::parseVarDecList()
{
    VarDecList *vdl = new VarDecList();
    VarDec *aux = parseVarDec();
    while (aux != nullptr)
    {
        vdl->add(aux);
        aux = parseVarDec();
    }
    return vdl;
}

// * FunDecList ::= (FunDec)+
FunDecList *Parser::parseFunDecList()
{
    FunDecList *fdl = new FunDecList();

    FunDec *fun = parseFunDec();

    if (!fun)
    {
        cout << "Error: expected at least one declared function (the main function)" << endl;
        exit(1);
    }

    do
    {
        fdl->add(fun);
        fun = parseFunDec();
    } while (fun != nullptr);

    return fdl;
}

// * FunDec ::= fun id ([ParamDecList]) [: Type] {Body}
FunDec *Parser::parseFunDec()
{
    FunDec *fd = nullptr;

    if (match(Token::FUN))
    {
        fd = new FunDec();

        if (!match(Token::ID))
        {
            cout << "Error: expected a name in the function declaration" << endl;
            exit(1);
        }

        fd->id = previous->text;

        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after the function name" << endl;
            exit(1);
        }

        // * ... [ParamDecList] ...
        // * ParamDecList ::= id: Type (, id: Type)*
        if (!check(Token::RP))
        {
            do
            {
                if (!match(Token::ID))
                {
                    cout << "Error: expected parameter name" << endl;
                    exit(1);
                }

                string paramName = previous->text;

                if (!match(Token::COLON))
                {
                    cout << "Error: expected ':' after parameter name" << endl;
                    exit(1);
                }

                if (!match(Token::ID))
                {
                    cout << "Error: expected parameter type" << endl;
                    exit(1);
                }

                string paramType = previous->text;

                fd->params.push_back(paramName);
                fd->params_types.push_back(paramType);
            } while (match(Token::COMMA));
        }

        if (!match(Token::RP))
        {
            cout << "Error: expected a ')'" << endl;
            exit(1);
        }

        // * ... [: Type] ...
        // * Type ::= id
        if (match(Token::COLON))
        {
            if (!match(Token::ID))
            {
                cout << "Error: expected return type after ':'" << endl;
                exit(1);
            }
            fd->type = previous->text;
        }
        else
        {
            fd->type = "void";
        }

        if (!match(Token::LB))
        {
            cout << "Error: expected a '{' before function body" << endl;
            exit(1);
        }

        fd->b = parseBody();

        if (!match(Token::RB))
        {
            cout << "Error: expected a '}' after function body" << endl;
            exit(1);
        }
    }

    return fd;
}

// * Body ::= VarDecList StmList
Body *Parser::parseBody()
{
    VarDecList *vdl = parseVarDecList();
    StatementList *sl = parseStatementList();
    return new Body(vdl, sl);
}

/*
 *  VarDec_1 ::= var id: Type [(; VarDec_2)*] | val id: Type [(; VarDec_2)*]
 *  VarDec_2 ::= var id: Type | val id: Type

 ! This vardec only handles declarations, not definition...
 ! So, something like this var a: Int = 2 is not accepted
 ! because vardec does not support assign operator (should be separated)
 */
VarDec *Parser::parseVarDec()
{
    VarDec *vd = nullptr;

    if (match(Token::VAR) || match(Token::VAL))
    {
        if (!match(Token::ID))
        {
            cout << "Error: expected an id for the variable declaration" << endl;
            exit(1);
        }

        string varName = previous->text;

        if (!match(Token::COLON))
        {
            cout << "Error: expected ':' after the id of the variable declaration" << endl;
            exit(1);
        }

        if (!match(Token::ID))
        {
            cout << "Error: expected a type for the variable" << endl;
            exit(1);
        }

        string varType = previous->text;

        list<string> vars;
        vars.push_back(varName);

        // * ... [(; VarDec_2)*] ...
        /*
        TODO: ask professor because I have problem with cases like var x:Int; var y: Int
        ! it seems that the semicolon is not well parse but I am not sure if that is a problem of the vardec or also of the stmtlist

        TODO: ask professor becuause cases like the following are not parsed well (my compiler has a limitation of how to handle the semicolons that are optional in Kotlin)
        val a: Int
        val b: Int
        val c: Int
        val t: Int

        a = 3
        b = 8
        c = 2
        t = 8

        val result: Boolean

        ! I obtain Error: expected a '}' after function body -> it seems that I have to declare the variables as separated as possible from the definitions...
        */
        while (match(Token::SEMICOLON))
        {
            if (match(Token::VAR) || match(Token::VAL))
            {
                if (!match(Token::ID))
                {
                    cout << "Error: expected an id for the variable declaration" << endl;
                    exit(1);
                }

                vars.push_back(previous->text);

                if (!match(Token::COLON))
                {
                    cout << "Error: expected ':' after the id of the variable declaration" << endl;
                    exit(1);
                }

                if (!match(Token::ID))
                {
                    cout << "Error: expected a type for the variable" << endl;
                    exit(1);
                }

                if (previous->text != varType) // ! for not to implement a list of types... (not like Kotlin)
                {
                    cout << "Error: all variables in the same line must have the same type" << endl;
                    exit(1);
                }
            }
        }

        vd = new VarDec(varType, vars);
    }

    return vd;
}

// * StmList ::= Stm [([;] Stm)*]
StatementList *Parser::parseStatementList()
{
    StatementList *sl = new StatementList();
    Stm *stmt = parseStatement();

    if (stmt)
    {
        sl->add(stmt);
    }

    // * ... [([;] Stm)*] ...
    while (true) // ! multiple stmts with optional semicolon
    {

        // ! optional to consume this token...
        if (match(Token::SEMICOLON))
        {
            stmt = parseStatement();
            if (!stmt)
            {
                break;
            }
            sl->add(stmt);
        }

        // ! verify if a stmt is beginning...
        else if (current->type == Token::ID || current->type == Token::PRINTLN ||
                 current->type == Token::PRINT || current->type == Token::IF ||
                 current->type == Token::FOR || current->type == Token::WHILE ||
                 current->type == Token::RETURN)
        {
            stmt = parseStatement();
            if (!stmt)
            {
                break;
            }
            sl->add(stmt);
        }
        else
        {
            break;
        }
    }

    return sl;
}

/*
 * Stm ::= id AugAssign CExp
 *       | id = CExp
 *       | println(CExp)
 *       | print(CExp)
 *       | if (CExp) {Body} [else {Body}]
 *       | for (id in CExp..CExp [step CExp]) {Body}
 *       | while (CExp) {Body}
 *       | return CExp
 */
Stm *Parser::parseStatement()
{
    Stm *s = nullptr;
    Exp *e = nullptr;
    Body *tb = nullptr;
    Body *fb = nullptr;

    // ? Why do we have this in the lab code
    if (current == nullptr)
    {
        cout << "Error: actual token is NULL" << endl;
        exit(1);
    }

    // * id = CExp
    // * id AugAssign CExp
    if (match(Token::ID))
    {
        string lex = previous->text;
        /*
         * AugAssign ::= +=
         *         | -=
         *         | *=
         *         | /=
         *         | %=
         */
        if (check(Token::AA_PLUS) || check(Token::AA_MINUS) ||
            check(Token::AA_MUL) || check(Token::AA_DIV) ||
            check(Token::AA_MOD))
        {
            AugmentedOp op;
            switch (current->type)
            {
            case Token::AA_PLUS:
                op = AA_PLUS_OP;
                break;
            case Token::AA_MINUS:
                op = AA_MINUS_OP;
                break;
            case Token::AA_MUL:
                op = AA_MUL_OP;
                break;
            case Token::AA_DIV:
                op = AA_DIV_OP;
                break;
            case Token::AA_MOD:
                op = AA_MOD_OP;
                break;
            default:
                cout << "Error: invalid augmented assign operator in the assign statement" << endl;
                exit(1);
            }
            advance();
            Exp *rhs = parseCExp();
            s = new AugmentedAssignStatement(lex, op, rhs);
        }

        else if (match(Token::ASSIGN))
        {
            e = parseCExp();
            s = new AssignStatement(lex, e);
        }

        else
        {
            cout << "Error: expected assigment operator or augmented assigment operator after the identifier." << endl;
            exit(1);
        }
    }

    // * println(CExp)
    else if (match(Token::PRINTLN))
    {
        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after 'println'." << endl;
            exit(1);
        }
        e = parseCExp();
        if (!match(Token::RP))
        {
            cout << "Error: expected a ')' after expression." << endl;
            exit(1);
        }
        s = new PrintLnStatement(e);
    }

    // * print(CExp)
    else if (match(Token::PRINT))
    {
        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after 'print'." << endl;
            exit(1);
        }
        e = parseCExp();
        if (!match(Token::RP))
        {
            cout << "Error: expected a ')' after expression." << endl;
            exit(1);
        }
        s = new PrintStatement(e);
    }

    // * if (CExp) {Body} [else {Body}]
    else if (match(Token::IF))
    {
        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after 'if' in if statement" << endl;
            exit(1);
        }

        e = parseCExp();

        if (!match(Token::RP))
        {
            cout << "Error: expected a ')' after 'if' in if statement" << endl;
            exit(1);
        }

        if (!match(Token::LB))
        {
            cout << "Error: expected a '{' after 'if' in if statement" << endl;
            exit(1);
        }

        tb = parseBody();

        if (!match(Token::RB))
        {
            cout << "Error: expected a '}' after 'if' in if statement" << endl;
            exit(1);
        }

        if (match(Token::ELSE))
        {
            if (!match(Token::LB))
            {
                cout << "Error: expected a '{' after 'else' in if statement" << endl;
                exit(1);
            }

            fb = parseBody();

            if (!match(Token::RB))
            {
                cout << "Error: expected a '}' after 'else' in if statement" << endl;
                exit(1);
            }
        }

        s = new IfStatement(e, tb, fb);
    }

    // * for (id in CExp..CExp [step CExp]) {Body}
    else if (match(Token::FOR))
    {
        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after 'for' in for statement" << endl;
            exit(1);
        }

        if (!match(Token::ID))
        {
            cout << "Error: expected iterator in for statement" << endl;
            exit(1);
        }

        string var = previous->text;

        if (!match(Token::IN))
        {
            cout << "Error: expected 'in' for statement" << endl;
            exit(1);
        }

        Exp *start = parseCExp();

        if (!match(Token::RANGE))
        {
            cout << "Error: expected '..' for statement" << endl;
            exit(1);
        }

        Exp *end = parseCExp();
        Exp *step = nullptr;

        if (match(Token::STEP))
        {
            step = parseCExp();
        }

        if (!match(Token::RP))
        {
            cout << "Error: expected a ')' after the for statement condition" << endl;
            exit(1);
        }

        if (!match(Token::LB))
        {
            cout << "Error: expected a '{' after the ')' in the for statement" << endl;
            exit(1);
        }

        tb = parseBody();

        if (!match(Token::RB))
        {
            cout << "Error: expected a '}' after the body of the for statement" << endl;
            exit(1);
        }

        s = new ForStatement(var, tb, start, end, step);
    }

    // * while (CExp) {Body}
    else if (match(Token::WHILE))
    {
        if (!match(Token::LP))
        {
            cout << "Error: expected a '(' after 'while' in while statement." << endl;
            exit(1);
        }

        e = parseCExp();

        if (!match(Token::RP))
        {
            cout << "Error: expected a ')' after condition in while statement." << endl;
            exit(1);
        }

        if (!match(Token::LB))
        {
            cout << "Error: expected a '{' in while statement." << endl;
            exit(1);
        }

        tb = parseBody();

        if (!match(Token::RB))
        {
            cout << "Error: expected a '}' after body in while statement." << endl;
            exit(1);
        }

        s = new WhileStatement(e, tb);
    }

    // * return CExp
    else if (match(Token::RETURN))
    {
        ReturnStatement *rs = new ReturnStatement();

        rs->e = parseCExp();

        if (rs->e == nullptr)
        {
            cout << "Error: expected an expression after 'return'" << endl;
            exit(1);
        }

        return rs;
    }
    return s;
}

// * CExp ::= LogicalExp ([ < | <= | >= | > | == | != ] LogicalExp)?
Exp *Parser::parseCExp()
{
    Exp *left = parseLogicalExp();
    while (check(Token::LT) || check(Token::LE) ||
           check(Token::GE) || check(Token::GT) ||
           check(Token::EQ) || check(Token::DIFF))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::LT:
            op = LT_OP;
            break;
        case Token::LE:
            op = LE_OP;
            break;
        case Token::GE:
            op = GE_OP;
            break;
        case Token::GT:
            op = GT_OP;
            break;
        case Token::EQ:
            op = EQ_OP;
            break;
        case Token::DIFF:
            op = DIFF_OP;
            break;
        default:
            cout << "Error: not valid operator in CExp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseLogicalExp();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * LogicalExp ::= OrExp ((&& | ||) OrExp)*
Exp *Parser::parseLogicalExp()
{
    Exp *left = parseOrExp();
    while (check(Token::LOG_AND) || check(Token::LOG_OR))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::LOG_AND:
            op = LOG_AND_OP;
            break;
        case Token::LOG_OR:
            op = LOG_OR_OP;
            break;
        default:
            cout << "Error: not valid operator in LogicalExp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseOrExp();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * OrExp ::= XorExp (or XorExp)*
Exp *Parser::parseOrExp()
{
    Exp *left = parseXorExp();
    while (check(Token::BW_OR))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::BW_OR:
            op = BW_OR_OP;
            break;
        default:
            cout << "Error: expected 'or' in OrExp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseXorExp();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * XorExp ::= AndExp (xor AndExp)*
Exp *Parser::parseXorExp()
{
    Exp *left = parseAndExp();
    while (check(Token::BW_XOR))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::BW_XOR:
            op = BW_XOR_OP;
            break;
        default:
            cout << "Error: expected 'xor' in OrExp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseAndExp();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * AndExp ::= ShiftExp (and ShiftExp)*
Exp *Parser::parseAndExp()
{
    Exp *left = parseShiftExp();
    while (check(Token::BW_AND))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::BW_AND:
            op = BW_AND_OP;
            break;
        default:
            cout << "Error: expected 'and' in OrExp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseShiftExp();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * ShiftExp ::= Exp (( shl | shr | ushr ) Exp)*
Exp *Parser::parseShiftExp()
{
    Exp *left = parseExpression();
    while (check(Token::BW_SHL) || check(Token::BW_SHR) || check(Token::BW_USHR))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::BW_SHL:
            op = BW_SHL_OP;
            break;
        case Token::BW_SHR:
            op = BW_SHR_OP;
            break;
        case Token::BW_USHR:
            op = BW_USHR_OP;
            break;
        default:
            cout << "Error: expected a shift operator in ShiftExp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseExpression();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * Exp ::= Term (( + | - ) Term)*
Exp *Parser::parseExpression()
{
    Exp *left = parseTerm();
    while (check(Token::PLUS) || check(Token::MINUS))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::PLUS:
            op = PLUS_OP;
            break;
        case Token::MINUS:
            op = MINUS_OP;
            break;
        default:
            cout << "Error: expected '+' or '-' in Exp" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

// * Term ::= Factor (( * | / | % ) Factor)*
Exp *Parser::parseTerm()
{
    Exp *left = parseFactor();
    while (check(Token::MUL) || check(Token::DIV) || check(Token::MOD))
    {
        BinaryOp op;
        switch (current->type)
        {
        case Token::MUL:
            op = MUL_OP;
            break;
        case Token::DIV:
            op = DIV_OP;
            break;
        case Token::MOD:
            op = MOD_OP;
            break;
        default:
            cout << "Error: expected '*' or '/' or '%' in Term" << endl;
            exit(1);
        }
        advance();
        Exp *right = parseFactor();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

/*
 * Factor ::= id
 *      | Num
 *      | Bool
 *      | (CExp)
 *      | PrefixOp Factor
 *      | id([ArgList])
 *      | id.("toInt" | "toLong"| "toUInt" | "toULong")()
 */
Exp *Parser::parseFactor()
{
    // * Factor ::= Num
    /*
    * Num ::= Digit+ ([ u | U ] [ l | L ]? | [ l | L ] [ u | U ]?)

    * Digit ::= 0
    *       | 1
    *       | 2
    *       | 3
    *       | 4
    *       | 5
    *       | 6
    *       | 7
    *       | 8
    *       | 9
    */
    if (match(Token::NUM))
    {
        const string &lex = previous->text;
        long long int val = stoll(lex.c_str(), nullptr, 10); // ! make sure we can operate large numbers thar are unsign long long int

        // ! read suffix
        bool seenU = false, seenL = false;

        // ! check cases like only u or U and only l or L
        if (check(Token::SUFFIX_u) || check(Token::SUFFIX_U))
        {
            seenU = true;
            advance();
        }
        if (check(Token::SUFFIX_l) || check(Token::SUFFIX_L))
        {
            seenL = true;
            advance();
        }

        // ! check cases like ul, lu, LU and UL
        if (!seenL && (check(Token::SUFFIX_l) || check(Token::SUFFIX_L)))
        {
            seenL = true;
            advance();
        }
        if (!seenU && (check(Token::SUFFIX_u) || check(Token::SUFFIX_U)))
        {
            seenU = true;
            advance();
        }

        numType type;

        // TODO: ask professor because test case 1 in which z = 100000 is assigned as int (eax) instead of long (rax)
        // ! classify the type
        if (!seenU && !seenL)
        {
            // ! if we do not have the type as suffix, we check the value... however this value can change in the checktype
            // ! technically this should not be done in parser because parser check only the structure but we could say it is an optimization xD
            if (val > INT32_MAX || val < INT32_MIN) // ? should the value be less than int32_min
            {
                type = LONG;
            }
            else
            {
                type = INT;
            }
        }
        else if (seenU && !seenL)
        {
            type = UINT;
        }
        else if (!seenU && seenL)
        {
            type = LONG;
        }
        else
        {
            type = ULONG;
        }

        return new NumberExp(val, type);
    }

    // * Factor ::= Bool
    /*
     * Bool ::= true
     * | false
     */
    else if (match(Token::TRUE))
    {
        return new BoolExp(true);
    }
    else if (match(Token::FALSE))
    {
        return new BoolExp(false);
    }

    // ! Factor ::= StringExp -> scan and parse string but not going to use it... maybe change it in the future...
    else if (match(Token::STRING))
    {
        return new StringExp(previous->text);
    }

    // * Factor ::= (CExp)
    else if (match(Token::LP))
    {
        Exp *expr = parseCExp();
        if (!match(Token::RP))
        {
            cout << "Error: expected ')' after the expression in the Factor" << endl;
            exit(1);
        }
        return expr;
    }

    // * Factor ::= PrefixOp Factor
    /*
     * PrefixOp ::= +
     *        | -
     *        | !
     *        | ++
     *        | --
     *        | inv
     */
    else if (current->type == Token::PLUS || current->type == Token::MINUS ||
             current->type == Token::NOT || current->type == Token::PRE_INC ||
             current->type == Token::PRE_DEC || current->type == Token::INV)
    {
        PrefixOp op;
        switch (current->type)
        {
        case Token::PLUS:
            op = POS_OP;
            break;
        case Token::MINUS:
            op = NEG_OP;
            break;
        case Token::NOT:
            op = NOT_OP;
            break;
        case Token::PRE_INC:
            op = PRE_INC_OP;
            break;
        case Token::PRE_DEC:
            op = PRE_DEC_OP;
            break;
        case Token::INV:
            op = INV_OP;
            break;
        default:
            cout << "Error: unexpected prefix operator in Factor" << endl;
            exit(1);
        }
        advance();
        return new PrefixExp(parseFactor(), op);
    }

    // * Factor ::= id([ArgList])
    // * ArgList ::= CExp (, CExp)*
    else if (match(Token::ID))
    {
        string id = previous->text;

        if (match(Token::LP))
        {
            FCallExp *call = new FCallExp();
            call->id = id;

            if (!check(Token::RP))
            {
                do
                {
                    call->arglist.push_back(parseCExp());
                } while (match(Token::COMMA));
            }

            if (!match(Token::RP))
            {
                cout << "Error: expected ')' at the end of the function call in Factor" << endl;
                exit(1);
            }
            return call;
        }

        // * Factor ::= id.("toInt" | "toLong" | "toUInt" | "toULong")()
        /*
        ! remember: an id before applying the function, our compiler does not parse somethig like (-1).toUInt()
        ! if I wanted that, instead of id, I should create a new rule X that can be a num, bool, cexp, etc.
        */
        else if (match(Token::POINT))
        {
            ConversionTypeFun convType;
            switch (current->type)
            {
            case Token::TO_INT:
                convType = TO_INT_FUN;
                break;
            case Token::TO_LONG:
                convType = TO_LONG_FUN;
                break;
            case Token::TO_U_INT:
                convType = TO_U_INT_FUN;
                break;
            case Token::TO_U_LONG:
                convType = TO_U_LONG_FUN;
                break;
            default:
                cout << "Error: invalid conversion type function in Factor" << endl;
                exit(1);
            }
            advance();

            if (!match(Token::LP))
            {
                cout << "Error: expected a '(' after the conversion type function in Factor" << endl;
                exit(1);
            }

            if (!match(Token::RP))
            {
                cout << "Error: expected a ')' after '(' in Factor" << endl;
                exit(1);
            }

            return new ConversionExp(id, convType);
        }

        // * Factor ::= id
        else
        {
            return new IdentifierExp(id);
        }
    }

    else
    {
        cout << "Error: invalid Factor" << endl;
        exit(1);
    }
}