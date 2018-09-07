#ifndef ARRAY_H
#define ARRAY_H

#include "nobject.h"

object::objectPtr Array (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayReadOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayPushBack (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayIterator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayIteratorGet (object::objectPtr obj, object::argsContainer& args);
object::objectPtr ArrayIteratorAssignOperator (object::objectPtr obj, object::argsContainer& args);

#endif
