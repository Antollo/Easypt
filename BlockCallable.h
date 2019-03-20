#ifndef BLOCKCALLABLE_H
#define BLOCKCALLABLE_H

#include "nobject.h"
#include "parser.h"
#include <forward_list>
#include <tuple>
#include <algorithm>

object::objectPtr BlockCallable (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableReturn (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableCallOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableEqualOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableIf (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableFor (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableWhile (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableThrow (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableTry (object::objectPtr obj, object::arrayType& args);
object::objectPtr BlockCallableThis (object::objectPtr obj, object::arrayType& args);

#endif // BLOCKCALLABLE_H
