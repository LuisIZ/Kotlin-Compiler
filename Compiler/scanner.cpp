#include <iostream>
#include <cstring>
#include "token.h"
#include "scanner.h"

using namespace std;

Scanner::Scanner(const char *s) : input(s), first(0), current(0) {}

bool is_white_space(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

// ! we do not deal with comments... so when testing we have to erase the comments

Token *Scanner::nextToken()
{
    Token *token;

    // ! if still pending tokens, pop them from queue...
    if (!pending.empty())
    {
        Token *t = pending.front();
        pending.pop();
        return t;
    }

    // * ignore whitespaces and identify end of program
    while (current < input.length() && is_white_space(input[current]))
        current++;
    if (current >= input.length())
        return new Token(Token::END);

    char c = input[current];
    first = current;

    // new scanning tokens in Num
    if (isdigit(c))
    {
        // ! consume digits
        while (current < input.length() && isdigit(input[current]))
            current++;

        // ! define token digit and save it in the queue (is pending)
        pending.push(new Token(Token::NUM, input, first, current-first));

        // ! lets check the existence of suffix...
        bool seenU = false, seenL = false;

        // ! only suffix u or U exist?
        if (current < input.length() && (input[current] == 'u' || input[current] == 'U'))
        {
            seenU = true;
            pending.push(new Token((input[current] == 'u') ? Token::SUFFIX_u : Token::SUFFIX_U, input, current, 1));
            current++;
        }

        // ! only suffix l or L exist?
        if (current < input.length() && (input[current] == 'l' || input[current] == 'L'))
        {
            seenU = true;
            pending.push(new Token((input[current] == 'l') ? Token::SUFFIX_l : Token::SUFFIX_L, input, current, 1));
            current++;
        }

        // ! a combination of the suffix exist (ul or lu)?
        if (!seenL && current < input.length() &&
            (input[current] == 'l' || input[current] == 'L'))
        {
            pending.push(new Token((input[current] == 'l') ? Token::SUFFIX_l : Token::SUFFIX_L, input, current, 1));
            current++;
        }
        if (!seenU && current < input.length() &&
            (input[current] == 'u' || input[current] == 'U'))
        {
            pending.push(new Token((input[current] == 'u') ? Token::SUFFIX_u : Token::SUFFIX_U, input, current, 1));
            current++;
        }

        // ! scanner return tokens based on the order of queue
        Token* t = pending.front();
        pending.pop();
        return t;
    }

    else if (c == '"')
    {
        current++;
        first = current;

        while (current < input.length() && input[current] != '"')
            current++;

        if (current < input.length())
        {
            current++;
            token = new Token(Token::STRING, input, first, current - first);
        }
        else
        {
            token = new Token(Token::ERR, c);
        }
    }

    else if (isalpha(c))
    {
        current++;
        while (current < input.length() && isalnum(input[current]))
            current++;
        string word = input.substr(first, current - first);

        // new scanning token in rule FunDecl
        if (word == "fun")
        {
            token = new Token(Token::FUN, word, 0, word.length());
        }

        // new scanning tokens in rule VarDec_1
        else if (word == "var")
        {
            token = new Token(Token::VAR, word, 0, word.length());
        }
        else if (word == "val")
        {
            token = new Token(Token::VAL, word, 0, word.length());
        }

        // new scanning tokens in rule Stm
        else if (word == "println")
        {
            token = new Token(Token::PRINTLN, word, 0, word.length());
        }
        else if (word == "print")
        {
            token = new Token(Token::PRINT, word, 0, word.length());
        }
        else if (word == "if")
        {
            token = new Token(Token::IF, word, 0, word.length());
        }
        else if (word == "else")
        {
            token = new Token(Token::ELSE, word, 0, word.length());
        }
        else if (word == "for")
        {
            token = new Token(Token::FOR, word, 0, word.length());
        }
        else if (word == "step")
        {
            token = new Token(Token::STEP, word, 0, word.length());
        }
        else if (word == "in")
        {
            token = new Token(Token::IN, word, 0, word.length());
        }
        else if (word == "while")
        {
            token = new Token(Token::WHILE, word, 0, word.length());
        }
        else if (word == "return")
        {
            token = new Token(Token::RETURN, word, 0, word.length());
        }

        // new scanning token in rule OrExp
        else if (word == "or")
        {
            token = new Token(Token::BW_OR, word, 0, word.length());
        }

        // new scanning token in rule XorExp
        else if (word == "xor")
        {
            token = new Token(Token::BW_XOR, word, 0, word.length());
        }

        // new scanning token in rule AndExp
        else if (word == "and")
        {
            token = new Token(Token::BW_AND, word, 0, word.length());
        }

        // new scanning token in rule ShiftExp
        else if (word == "shl")
        {
            token = new Token(Token::BW_SHL, word, 0, word.length());
        }
        else if (word == "shr")
        {
            token = new Token(Token::BW_SHR, word, 0, word.length());
        }
        else if (word == "ushr")
        {
            token = new Token(Token::BW_USHR, word, 0, word.length());
        }

        // new scanning token in rule PrefixOp
        else if (word == "inv")
        {
            token = new Token(Token::INV, word, 0, word.length());
        }

        // new scanning tokens for rule Factor
        else if (word == "toInt")
        {
            token = new Token(Token::TO_INT, word, 0, word.length());
        }
        else if (word == "toLong")
        {
            token = new Token(Token::TO_LONG, word, 0, word.length());
        }
        else if (word == "toUInt")
        {
            token = new Token(Token::TO_U_INT, word, 0, word.length());
        }
        else if (word == "toULong")
        {
            token = new Token(Token::TO_U_LONG, word, 0, word.length());
        }

        // new scanning tokens in rule Bool
        else if (word == "true")
        {
            token = new Token(Token::TRUE, word, 0, word.length());
        }
        else if (word == "false")
        {
            token = new Token(Token::FALSE, word, 0, word.length());
        }

        // new scanning token in FunDecl
        else
        {
            token = new Token(Token::ID, word, 0, word.length());
        }
    }

    else if (strchr("():{},;+-*/%=.<>!&|", c))
    {
        switch (c)
        {
        case '(':
            token = new Token(Token::LP, c);
            break;
        case ')':
            token = new Token(Token::RP, c);
            break;
        case ':':
            token = new Token(Token::COLON, c);
            break;
        case '{':
            token = new Token(Token::LB, c);
            break;
        case '}':
            token = new Token(Token::RB, c);
            break;
        case ',':
            token = new Token(Token::COMMA, c);
            break;
        case ';':
            token = new Token(Token::SEMICOLON, c);
            break;
        case '+':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::AA_PLUS, "+=", 0, 2);
                current++;
            }
            else if (current + 1 < input.length() && input[current + 1] == '+')
            {
                token = new Token(Token::PRE_INC, "++", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::PLUS, c);
            }
            break;
        case '-':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::AA_MINUS, "-=", 0, 2);
                current++;
            }
            else if (current + 1 < input.length() && input[current + 1] == '-')
            {
                token = new Token(Token::PRE_DEC, "--", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::MINUS, c);
            }
            break;
        case '*':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::AA_MUL, "*=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::MUL, c);
            }
            break;
        case '/':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::AA_DIV, "/=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::DIV, c);
            }
            break;
        case '%':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::AA_MOD, "%=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::MOD, c);
            }
            break;
        case '=':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::EQ, "==", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::ASSIGN, c);
            }
            break;
        case '.':
            if (current + 1 < input.length() && input[current + 1] == '.')
            {
                token = new Token(Token::RANGE, "..", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::POINT, c);
            }
            break;
        case '<':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::LE, "<=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::LT, c);
            }
            break;
        case '>':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::GE, ">=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::GT, c);
            }
            break;
        case '!':
            if (current + 1 < input.length() && input[current + 1] == '=')
            {
                token = new Token(Token::DIFF, "!=", 0, 2);
                current++;
            }
            else
            {
                token = new Token(Token::NOT, c);
            }
            break;
        case '&':
            if (current + 1 < input.length() && input[current + 1] == '&')
            {
                token = new Token(Token::LOG_AND, "&&", 0, 2);
                current++;
            }
            else
            {
                cout << "Error in scanner: unknown token" << endl;
                token = new Token(Token::ERR, c);
            }
            break;
        case '|':
            if (current + 1 < input.length() && input[current + 1] == '|')
            {
                token = new Token(Token::LOG_OR, "||", 0, 2);
                current++;
            }
            else
            {
                cout << "Error in scanner: unknown token" << endl;
                token = new Token(Token::ERR, c);
            }
            break;

        default:
            cout << "Error in scanner: unknown token" << endl;
            token = new Token(Token::ERR, c);
        }
        current++;
    }

    // new scanning extra tokens (outside grammar)
    else
    {
        token = new Token(Token::ERR, c);
        current++;
    }

    return token;
}

void Scanner::reset()
{
    first = 0;
    current = 0;
}

Scanner::~Scanner() {}

// new scanning extra token (outside grammar)
void test_scanner(Scanner *scanner)
{
    Token *current;
    cout << "Initiating Scanner:" << endl
         << endl;
    while ((current = scanner->nextToken())->type != Token::END)
    {
        if (current->type == Token::ERR)
        {
            cout << "Error in scanner - invalid character: " << current->text << endl;
            break;
        }
        else
        {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END)" << endl;
    delete current;
}