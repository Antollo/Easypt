#ifndef BLOCKCALLABLE_H
#define BLOCKCALLABLE_H

#include "nobject.h"
#include "parser.h"
#include <forward_list>

object::objectPtr BlockCallable (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableCallOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableEqualOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableIf (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableFor (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableWhile (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableThrow (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BlockCallableTry (object::objectPtr obj, object::argsContainer& args);

#endif // BLOCKCALLABLE_H
