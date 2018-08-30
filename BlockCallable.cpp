#include "BlockCallable.h"

//BlockCallable constructor
object::objectPtr BlockCallable (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(name("Callable"));
    ret->addSignature(obj->getName());
    ret->addChild(obj->READ(name("for"))->copy());
    ret->addChild(obj->READ(name("while"))->copy());
    ret->addChild(obj->READ(name("if"))->copy());
    ret->addChild(obj->READ(name("=="))->copy());
    ret->addChild(obj->READ(name("callOperator"))->copy());
    ret->getValue() = std::list<expression>();
    return ret;
}
//BlockCallable methods
object::objectPtr BlockCallableEqualOperator (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        bool firstComparison = ((obj->getParent()->getSignatures() == args[0]->getSignatures()) && (obj->getParent()->getChildren() == args[0]->getChildren()));
        if (firstComparison)
            firstComparison = (std::any_cast<std::list<expression>>(args[0]->getValue()) == std::any_cast<std::list<expression>>(obj->getParent()->getValue()));
        object::objectPtr ret = obj->READ(name("Boolean"), true)->CALL();
        ret->getValue() = firstComparison;
        return ret;
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
/*enum type {call, read, readcall};

    virtual std::list<expression>& getExpressionList() = 0;
    virtual name& getName() = 0;
    virtual bool& getForceCreate() = 0;
    virtual bool& getSearchInParent() = 0;
    virtual expression& getExpression() = 0;
    virtual type getType() = 0;*/
object::objectPtr evaluateExpression(const expression& exp, object::objectPtr parent)
{
    object::objectPtr temp = parent;
    //To keep orphans alive
    std::forward_list<object::objectPtr> expressionTemp;
    for(const std::shared_ptr<action>& act : exp)
    {
        expressionTemp.push_front(temp);
        switch(act->getType())
        {
        case action::type::read:
            temp = temp->READ(act->getName(), act->getSearchInParent(), act->getForceCreate());
            break;
        case action::type::readcall:
            temp = temp->READCALL(evaluateExpression(act->getExpression(), parent));
            break;
        case action::type::call:
            object::argsContainer args;
            args.resize(act->getExpressionList().size());
            int it = 0;
            for(const expression& exp : act->getExpressionList())
                args[it++] = evaluateExpression(exp, parent);
            temp = temp->CALL(args);
            break;
        }
    }
    return temp;
}
object::objectPtr BlockCallableCallOperator (object::objectPtr obj, object::argsContainer& args)
{
    //TODO make args array
    //TODO return something
    std::list<expression> expressions = std::any_cast<std::list<expression>>(obj->getParent()->getValue());
    object::objectPtr parent = obj->getParent();
    for(const expression& exp : expressions)
        evaluateExpression(exp, parent);//->debugTree(0);
    return obj->READ(name("Null"), true)->CALL();
}
object::objectPtr BlockCallableIf (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 2 || args.size() == 3)
    {
        if (args[0]->hasSignature(name("Basic")))
        {
            bool boolean = std::any_cast<bool>(args[0]->READ(name("toBoolean"))->CALL()->getValue());
            if (boolean)
            {
                args[1]->callWithParent(obj);
                //args[1]->CALL();
                return args[0];
            }
            else
            {
                if ( args.size() == 3)
                    args[2]->callWithParent(obj);
                return args[0];
            }
        }
        throw(exception("First argument is not Basic in ", obj->getFullNameString()));
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BlockCallableFor (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 4)
    {
        args[0]->CALL();
        if (!args[1]->hasSignature(name("Basic")))
            throw(exception("First argument is not Basic in ", obj->getFullNameString()));
        while (std::any_cast<bool>(args[1]->READ(name("toBoolean"))->CALL()->getValue()))
        {
            args[3]->callWithParent(obj);
            args[2]->callWithParent(obj);
            if (!args[1]->hasSignature(name("Basic")))
                throw(exception("First argument is not Basic in ", obj->getFullNameString()));
        }
        return args[1];
    }
    throw(exception("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
//object::objectPtr BlockCallableWhile (object::objectPtr obj, object::argsContainer& args);
