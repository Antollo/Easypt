#ifndef ARRAY_H
#define ARRAY_H

#include "nobject.h"

object::objectPtr Array0 (object::objectPtr obj, object::argsContainer& args);
object::objectPtr Array1 (object::objectPtr obj, object::argsContainer& args);
object::objectPtr Array2 (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayReadOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayPushBack (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayEqualOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayIterator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayIteratorGet (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayIteratorReferenceAssignOperator (object::objectPtr obj, object::argsContainer& args);

#endif
