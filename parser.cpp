#include "parser.h"

//#define DEBUG

parser::parser(const char* newSource, int newLast, object::objectRawPtr newRoot)
    : source(newSource), last(newLast), Root(newRoot), iterator(0) {};

int parser::numberOfSlashes(const int& i)
{
    int ret = i;
    while (source[ret] == '\\') ret--;
    return i - ret;
}

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
    int ret = iterator + 1;
    if (what == '"')
    {
        while (ret < last)
        {
            if (source[ret] == what && numberOfSlashes(ret - 1) % 2 == 0)
                return ret;
            ret++;
        }
        return ret;
    }
    bool quotemarksSwitch = false;
    int roundBracketsCounter = 0, curlyBracketsCounter = 0, squareBracketsCounter = 0;
    while (ret < last && (roundBracketsCounter != 0 || curlyBracketsCounter != 0 ||
            squareBracketsCounter != 0 || quotemarksSwitch == true ||
            source[ret] != what ))
    {
        switch (source[ret])
        {
            case '(':
                if (!quotemarksSwitch) roundBracketsCounter++;
                break;
            case ')':
                if (!quotemarksSwitch) roundBracketsCounter--;
                break;
            case '{':
                if (!quotemarksSwitch) curlyBracketsCounter++;
                break;
            case '}':
                if (!quotemarksSwitch) curlyBracketsCounter--;
                break;
            case '[':
                if (!quotemarksSwitch) squareBracketsCounter++;
                break;
            case ']':
                if (!quotemarksSwitch) squareBracketsCounter--;
                break;
            case '"':
                if (numberOfSlashes(ret - 1) % 2 == 0) quotemarksSwitch = !quotemarksSwitch;
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
    bool searchInParent = true, forceCreate =  false, automatic = false;
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
                str->getValue() = parseString(source + iterator + 1, temp - iterator - 1);
                str->setName(std::string(source + iterator, temp - iterator + 1));
                Root->addChild(str);
            }
            expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator + 1), searchInParent));
            searchInParent = false;
            forceCreate = false;
			automatic = false;
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
                    str->setName(std::string(source + iterator, temp - iterator + 1));
                    Root->addChild(str);
                }
                expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator + 1), searchInParent));
                searchInParent = false;
                forceCreate = false;
				automatic = false;
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
                        num->setName(std::string(source + iterator, temp - iterator));
                    }
                    else
                    {
                        num = parser::Root->READ(name("Double"), true)->CALL();
                        num->getValue() = std::atof(source + iterator);
                        num->setName(std::string(source + iterator, temp - iterator));
                    }
                    Root->addChild(num);
                }
                expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator), searchInParent));
                searchInParent = false;
                forceCreate = false;
				automatic = false;
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
				if (std::strncmp(source + iterator, "auto", 4) == 0)
				{
					forceCreate = true;
					automatic = true;
					#if defined(DEBUG)
					std::cout << ">auto \n";
					#endif
					iterator = temp + 1;
					break;
				}
                #if defined(DEBUG)
                std::cout<<">read <"<<std::string(source + iterator, temp - iterator)<<"> "<<forceCreate<<"\n";
                #endif
                expressions.back().push_back(std::make_shared<read>(std::string(source + iterator, temp - iterator), searchInParent, forceCreate, automatic));
                searchInParent = false;
                forceCreate = false;
				automatic = false;
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

std::string parser::parseString(const char* source, int length)
{
    std::string ret;
    ret.reserve(length);
    for (int i=0; i < length; i++)
    {
        if (source[i] != '\\')
            ret.push_back(source[i]);
        else
        {
            switch (source[++i])
            {
            case '"':
                ret.push_back('"');
                break;
            case '\\':
                ret.push_back('\\');
                break;
            case 'a':
                ret.push_back('\a');
                break;
            case 'b':
                ret.push_back('\b');
                break;
            case 'f':
                ret.push_back('\f');
                break;
            case 'n':
                ret.push_back('\n');
                break;
            case 'r':
                ret.push_back('\r');
                break;
            case 't':
                ret.push_back('\t');
                break;
            case 'v':
                ret.push_back('\v');
                break;
            case '\n':
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ret.push_back((source[i]-'0')*100 + (source[i+1]-'0')*10 + (source[i+2]-'0'));
                i += 2;
                break;
            }
        }
    }
    return ret;
}