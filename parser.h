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
    virtual bool& getForceCreate() = 0;
	virtual bool& getAutomatic() = 0;
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
    bool& getForceCreate() override  { throw(Parser("Error in parser.")); }
	bool& getAutomatic() override  { throw(Parser("Error in parser.")); }
    bool& getSearchInParent() override  { throw(Parser("Error in parser.")); }
    expression& getExpression() override  { throw(Parser("Error in parser.")); }
    type getType() override { return type::call; };
private:
    std::list<expression> expressionList;
};

class read : public action
{
public:
    read(name newName, bool newSearchInParent, bool newForceCreate = false, bool newAutomatic = false)
        : _name(newName), searchInParent(newSearchInParent), forceCreate(newForceCreate), automatic(newAutomatic) {};
    std::list<expression>& getExpressionList() override { throw(Parser("Error in parser.")); }
    name& getName() override  { return _name; }
    bool& getForceCreate() override  { return forceCreate; }
	bool& getAutomatic() override  { return automatic; }
    bool& getSearchInParent() override { return searchInParent; }
    expression& getExpression() override { throw(Parser("Error in parser.")); }
    type getType() override { return type::read; };
private:
    name _name;
    bool searchInParent, forceCreate, automatic;
};

class readcall : public action
{
public:
    readcall(expression newExpression)
        : _expression(newExpression) {};
    std::list<expression>& getExpressionList() override { throw(Parser("Error in parser.")); }
    name& getName() override  { throw(Parser("Error in parser.")); }
    bool& getForceCreate() override  { throw(Parser("Error in parser.")); }
	bool& getAutomatic() override  { throw(Parser("Error in parser.")); }
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
