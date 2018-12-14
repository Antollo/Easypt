#include "BlockCallable.h"

//BlockCallable constructor
object::objectPtr BlockCallable (object::objectPtr obj, object::argsContainer& args)
{
    object::objectPtr ret = obj->READ(name("Object"), true)->CALL();
    ret->addSignature(name("Callable"));
    ret->addSignature(obj->getName());
    for (auto& child : obj->getChildren())
        ret->addChild(child.second->copy());
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
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
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
typedef std::tuple<std::list<expression>::const_iterator*, std::list<expression>::const_iterator, object::objectPtr> returnValueTriplet;
object::objectPtr BlockCallableReturn (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        object::objectPtr parent = obj->getParent();
        returnValueTriplet& rvt = *std::any_cast<returnValueTriplet>(&parent->READ(name("returnValueTriplet"))->getValue());
        *(std::get<0>(rvt)) = std::get<1>(rvt);
        std::get<2>(rvt) = args[0];
        return args[0];
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BlockCallableCallOperator (object::objectPtr obj, object::argsContainer& args)
{
    std::list<expression> expressions = std::any_cast<std::list<expression>>(obj->getParent()->getValue());
    object::objectPtr parent = obj->getParent();
    parent->addChild(obj->READ(name("Array"), true)->CALL()->setValue(args)->setName("args"));
    std::list<expression>::const_iterator it = expressions.begin();
    parent->addChild(makeObject(returnValueTriplet(&it, std::prev(expressions.end()), constructObject(obj, "Object", 0)), name("returnValueTriplet")));
    while (it !=  expressions.end())
        evaluateExpression(*(it++), parent);
    return std::get<2>(std::any_cast<returnValueTriplet>(parent->READ(name("returnValueTriplet"))->getValue()));
}
object::objectPtr BlockCallableIf (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 2 || args.size() == 3)
    {
        if (args[0]->hasSignature(name("Boolean")))
        {
            bool boolean = std::any_cast<bool>(args[0]->getValue());
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
        else if (args[0]->hasSignature(name("Basic")))
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
        throw(WrongTypeOfArgument("First argument is not Basic in ", obj->getFullNameString()));
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BlockCallableFor (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 4)
    {
        object::objectPtr Root = obj->READ(name("Root"),true);
        while (std::any_cast<bool>(args[0]->CALL(args[1])->READ(name("toBoolean"))->CALL()->getValue()))
        {
            args[3]->callWithParent(obj);

            if (args[2]->getParent() == Root) args[2]->callWithParent(obj);
            else args[2]->CALL();
        }
        return args[3];
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BlockCallableWhile (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 2)
    {
        if (!args[0]->hasSignature(name("Basic")))
            throw(WrongTypeOfArgument("First argument is not Basic in ", obj->getFullNameString()));
        while (std::any_cast<bool>(args[0]->READ(name("toBoolean"))->CALL()->getValue()))
        {
            args[1]->callWithParent(obj);
            if (!args[0]->hasSignature(name("Basic")))
                throw(WrongTypeOfArgument("First argument is not Basic in ", obj->getFullNameString()));
        }
        return args[1];
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BlockCallableThrow (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 1)
    {
        throw(args[0]);
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}
object::objectPtr BlockCallableTry (object::objectPtr obj, object::argsContainer& args)
{
    if (args.size() == 2)
    {
        try
        {
            object::objectPtr ret = args[0]->callWithParent(obj);
            return ret;
        }
        catch (exception& e)
        {
            args[1]->CALL(constructObject(obj, "String", e.getMessage()));
        }
        catch (std::exception& e)
        {
            args[1]->CALL(constructObject(obj, "String", "Unknown exception: " + std::string(e.what())));
        }
        catch (object::objectPtr& e)
        {
           args[1]->CALL(e);
        }
        return obj->getParent();
    }
    throw(WrongNumberOfArguments("Wrong number (", std::to_string(args.size()),") of arguments while calling ", obj->getFullNameString()));
}