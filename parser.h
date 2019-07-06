#ifndef PARSER_H
#define PARSER_H

#include "nobject.h"
#include <list>
#include <cctype>
#include <cstring>

class action;
using expression = std::list<std::shared_ptr<action>> ;

class action
{
public:
    enum type {call, read, readcall};

    virtual std::list<expression>& getExpressionList() = 0;
    virtual name& getName() = 0;
    virtual object::forceCreateMode& getForceCreateMode() = 0;
    virtual bool& getSearchInParent() = 0;
    virtual expression& getExpression() = 0;
    virtual type getType() = 0;
};

class call : public action
{
public:
    call(std::list<expression> newExpressionList)
        : expressionList(newExpressionList) {};
    std::list<expression>& getExpressionList() override { return expressionList; }
    name& getName() override { throw(Parser("Error in parser.")); }
    object::forceCreateMode& getForceCreateMode() override  { throw(Parser("Error in parser.")); }
    bool& getSearchInParent() override  { throw(Parser("Error in parser.")); }
    expression& getExpression() override  { throw(Parser("Error in parser.")); }
    type getType() override { return type::call; };
private:
    std::list<expression> expressionList;
};

class read : public action
{
public:
    read(name newName, bool newSearchInParent, bool forceCreate = false, bool automatic = false, bool stack = false)
        : _name(newName), searchInParent(newSearchInParent), mode(object::forceCreateMode::none)
    {
        if (automatic)
        {
            mode = object::forceCreateMode::automatic;
            return;
        }
        if (stack)
        {
            mode = object::forceCreateMode::stack;
            return;
        }
        if (forceCreate)
        {
            mode = object::forceCreateMode::var;
            return;
        }
    };
    std::list<expression>& getExpressionList() override { throw(Parser("Error in parser.")); }
    name& getName() override  { return _name; }
    object::forceCreateMode& getForceCreateMode() override { return mode; }
    bool& getSearchInParent() override { return searchInParent; }
    expression& getExpression() override { throw(Parser("Error in parser.")); }
    type getType() override { return type::read; };
private:
    name _name;
    bool searchInParent;
    object::forceCreateMode mode;
};

class readcall : public action
{
public:
    readcall(expression newExpression)
        : _expression(newExpression) {};
    std::list<expression>& getExpressionList() override { throw(Parser("Error in parser.")); }
    name& getName() override  { throw(Parser("Error in parser.")); }
    object::forceCreateMode& getForceCreateMode() override  { throw(Parser("Error in parser.")); }
    bool& getSearchInParent() override { throw(Parser("Error in parser.")); }
    expression& getExpression() override { return _expression; }
    type getType() override { return type::readcall; };
private:
    expression _expression;
};

class parser
{
    public:
        parser(const char* newSource, int newLast, object::objectRawPtr newRoot);
        int numberOfSlashes(const int& i);
        std::list<expression> parse();
        void eatTrash();
        void eatTrash(int& i);
        void eatTrashBackward(int& i);
        int findNext(char what);
        bool isAlnum(char c)
        {
            return std::isalpha(c) || std::isdigit(c);
        }
        bool isOperator(char c)
        {
            switch(c)
            {
            case '+':
            case '-':
            case '=':
            case '<':
            case '>':
            case '*':
            case '%':
            case '/':
            case '!':
            case '~':
            case '&':
            case '|':
            case '^':
            case '_':
                return true;
                break;
            default:
                return false;
                break;
            }
        }
        std::string parseString(const char* source, int length);
    private:
        const char* source;
        int last;
        object::objectRawPtr Root;
        int iterator;
};

#endif // PARSER_H
