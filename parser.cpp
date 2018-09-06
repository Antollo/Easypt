#include "parser.h"

//#define DEBUG

parser::parser(const char* newSource, int newLast, object::objectPtr newRoot)
    : source(newSource), last(newLast), Root(newRoot), iterator(0) {};

void parser::eatTrash()
{
    bool comment = false;
    while ( iterator < last && (std::isspace(source[iterator]) || comment || source[iterator] == '#'))
    {
        if (source[iterator] == '#')
            comment = !comment;
        iterator++;
    }
}

void parser::eatTrash(int& i)
{
    bool comment = false;
    while ( i < last  && (std::isspace(source[i]) || comment || source[i] == '#'))
    {
        i++;
        if (source[i] == '#')
            comment = !comment;
    }
}

void parser::eatTrashBackward(int& i)
{
    bool comment = false;
    while ( i > 0  && (std::isspace(source[i]) || comment || source[i] == '#'))
    {
        i--;
        if (source[i] == '#')
            comment = !comment;
    }
}

int parser::findNext(char what)
{
    bool quotemarksSwitch = false;
    int roundBracketsCounter = 0, curlyBracketsCounter = 0, squareBracketsCounter = 0, ret = iterator + 1;
    while (ret < last && (roundBracketsCounter != 0 || curlyBracketsCounter != 0 ||
            squareBracketsCounter != 0 || quotemarksSwitch == true || source[ret] != what))
    {
        switch (source[ret])
        {
        case '(':
            roundBracketsCounter++;
            break;
        case ')':
            roundBracketsCounter--;
            break;
        case '{':
            curlyBracketsCounter++;
            break;
        case '}':
            curlyBracketsCounter--;
            break;
        case '[':
            squareBracketsCounter++;
            break;
        case ']':
            squareBracketsCounter--;
            break;
        case '"':
            quotemarksSwitch = !quotemarksSwitch;
            break;
        }

        ret++;
    }
    return ret;
}

std::list<expression> parser::parse()
{
    std::list<expression> expressions;
    int temp;
    //searchInParent means that new expression is starting
    bool searchInParent = true, forceCreate =  false;
    expressions.emplace_back();
    while(true)
    {
        if (iterator > last)
            return expressions;
        eatTrash();
        switch (source[iterator])
        {
        case '(':
            {
                temp = findNext(')');
                #if defined(DEBUG)
                std::cout<<">call <"<<std::string(source + iterator + 1, temp - iterator - 1)<<"> "<<temp - iterator - 1<<"\n";
                #endif
                if(temp - iterator - 1)
                {
                    parser internal(source + iterator + 1, temp - iterator - 1, Root);
                    expressions.back().push_back(std::make_shared<call>(internal.parse()));
                }
                else
                {
                    expressions.back().push_back(std::make_shared<call>(std::list<expression>()));
                }

                iterator = temp + 1;
                break;
            }
        case '[':
            {
                temp = findNext(']');
                #if defined(DEBUG)
                std::cout<<">readcall <"<<std::string(source + iterator + 1, temp - iterator - 1)<<">\n";
                #endif
                parser internal(source + iterator + 1, temp - iterator - 1, Root);
                expressions.back().push_back(std::make_shared<readcall>(internal.parse().front()));
                iterator = temp + 1;
                break;
            }
        case '"':
            temp = findNext('"');
            if (!Root->hasChild(name(std::string(source + iterator, temp - iterator + 1))))
            {
                object::objectPtr str = parser::Root->READ(name("String"), true)->CALL();
                str->getValue() = std::string(source + iterator + 1, temp - iterator - 1);
                str->getName() = name(std::string(source + iterator, temp - iterator + 1));
                Root->addChild(str);
            }
            expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator + 1), searchInParent, false));
            searchInParent = false;
            forceCreate = false;
            #if defined(DEBUG)
            std::cout<<">str <"<<std::string(source + iterator, temp - iterator + 1)<<">\n";
            #endif
            iterator = temp + 1;
            break;
        case '{':
            {
                temp = findNext('}');
                if (!Root->hasChild(name(std::string(source + iterator, temp - iterator + 1))))
                {
                    object::objectPtr str = parser::Root->READ(name("BlockCallable"), true)->CALL();
                    parser internal(source + iterator + 1, temp - iterator - 1, Root);
                    str->getValue() = internal.parse();
                    str->getName() = name(std::string(source + iterator, temp - iterator + 1));
                    Root->addChild(str);
                }
                expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator + 1), searchInParent, false));
                searchInParent = false;
                forceCreate = false;
                #if defined(DEBUG)
                std::cout<<">obj <"<<std::string(source + iterator, temp - iterator + 1)<<">\n";
                #endif
                iterator = temp + 1;
                break;
            }
        case '.':
            #if defined(DEBUG)
            std::cout<<">. \n";
            #endif
            iterator++;
            break;
        case ',':
            #if defined(DEBUG)
            std::cout<<">, \n";
            #endif
            searchInParent = true;
            expressions.emplace_back();
            iterator++;
            break;
        case ';':
            #if defined(DEBUG)
            std::cout<<">; \n";
            #endif
            searchInParent = true;
            expressions.emplace_back();
            iterator++;
            break;
        default:
            if (std::isdigit(source[iterator]) || (source[iterator] == '-' && searchInParent))
            {
                //Expecting number literal
                bool dotEncountered = false, minusEncountered = false;
                temp = iterator;
                while (temp < last && (std::isdigit(source[temp])
                    || (source[temp] == '.' && dotEncountered == false && temp+1 <= last && std::isdigit(source[temp+1]))
                    || (source[temp] == '-' && minusEncountered == false)))
                {
                    if (source[temp] == '.') dotEncountered = true;
                    if (source[temp] == '-') minusEncountered = true;
                    temp++;
                }
                if (!Root->hasChild(name(std::string(source + iterator, temp - iterator))))
                {
                    object::objectPtr num;
                    if (dotEncountered == false)
                    {
                        num = parser::Root->READ(name("Int"), true)->CALL();
                        num->getValue() = std::atoi(source + iterator);
                        num->getName() = name(std::string(source + iterator, temp - iterator));
                    }
                    else
                    {
                        num = parser::Root->READ(name("Object"), true)->CALL();
                        //object::objectPtr num = parser::Root->READ(name("Double"), true)->CALL();
                        //num->getValue() = std::atof(source + iterator);
                        //num->getName() = name(std::string(source + iterator, temp - iterator));
                    }
                    Root->addChild(num);
                }
                expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator), searchInParent, false));
                searchInParent = false;
                forceCreate = false;
                #if defined(DEBUG)
                std::cout<<">num <"<<std::string(source + iterator, temp - iterator)<<"> "<<std::atoi(source + iterator)<<"\n";
                #endif
                iterator = temp;
            }
            else if (isAlnum(source[iterator]) || isOperator(source[iterator]))
            {
                //Expecting read
                temp = iterator;
                while (temp <= last && (isAlnum(source[temp]) || isOperator(source[temp]))) temp++;
                if (std::strncmp(source + iterator, "var", 3) == 0)
                {
                    forceCreate = true;
                    #if defined(DEBUG)
                    std::cout<<">var \n";
                    #endif
                    iterator = temp + 1;
                    break;
                }
                #if defined(DEBUG)
                std::cout<<">read <"<<std::string(source + iterator, temp - iterator)<<"> "<<forceCreate<<"\n";
                #endif
                expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator), searchInParent, forceCreate));
                searchInParent = false;
                forceCreate = false;
                iterator = temp;
            }
            else
            {
                iterator++;
            }
            break;
        }
    }
}
