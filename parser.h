#ifndef PARSER_H
#define PARSER_H

#include "nobject.h"
#include <list>
#include <cctype>
#include <cstring>

class action;
typedef std::list<std::shared_ptr<action>> expression;

class action
{
public:
    enum type {call, read, readcall};

    virtual std::list<expression>& getExpressionList() = 0;
    virtual name& getName() = 0;
    virtual bool& getForceCreate() = 0;
    virtual bool& getSearchInParent() = 0;
    virtual expression& getExpression() = 0;
    virtual type getType() = 0;
};

class call : public action
{
public:
    call(std::list<expression> newExpressionList)
        : expressionList(newExpressionList) {};
    std::list<expression>& getExpressionList() { return expressionList; }
    name& getName() { throw(exception("Error in parser.")); }
    bool& getForceCreate() { throw(exception("Error in parser.")); }
    bool& getSearchInParent() { throw(exception("Error in parser.")); }
    expression& getExpression() { throw(exception("Error in parser.")); }
    type getType() { return type::call; };
private:
    std::list<expression> expressionList;
};

class read : public action
{
public:
    read(name newName, bool newSearchInParent, bool newForceCreate)
        : _name(newName), searchInParent(newSearchInParent), forceCreate(newForceCreate) {};
    std::list<expression>& getExpressionList() { throw(exception("Error in parser.")); }
    name& getName() { return _name; }
    bool& getForceCreate() { return forceCreate; }
    bool& getSearchInParent() { return searchInParent; }
    expression& getExpression() { throw(exception("Error in parser.")); }
    type getType() { return type::read; };
private:
    name _name;
    bool searchInParent, forceCreate;
};

class readcall : public action
{
public:
    readcall(expression newExpression)
        : _expression(newExpression) {};
    std::list<expression>& getExpressionList() { throw(exception("Error in parser.")); }
    name& getName() { throw(exception("Error in parser.")); }
    bool& getForceCreate() { throw(exception("Error in parser.")); }
    bool& getSearchInParent() { throw(exception("Error in parser.")); }
    expression& getExpression() { return _expression; }
    type getType() { return type::readcall; };
private:
    expression _expression;
};

class parser
{
    public:
        parser(const char* newSource, int newLast, object::objectPtr newRoot);
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
            case ':':
            case '*':
            case '%':
            case '/':
            case '!':
                return true;
                break;
            default:
                return false;
                break;
            }
        }
    private:
        const char* source;
        int last;
        object::objectPtr Root;
        int iterator;
};

#endif // PARSER_H
