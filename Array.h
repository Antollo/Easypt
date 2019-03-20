#ifndef ARRAY_H
#define ARRAY_H

#include "nobject.h"

object::objectPtr Array0 (object::objectPtr obj, object::arrayType& args);
object::objectPtr Array1 (object::objectPtr obj, object::arrayType& args);
object::objectPtr Array2 (object::objectPtr obj, object::arrayType& args);
object::objectPtr ArrayReadOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr ArrayPushBack (object::objectPtr obj, object::arrayType& args);
object::objectPtr ArrayEqualOperator (object::objectPtr obj, object::arrayType& args);
object::arrayType ArraySubarray(object::arrayType::iterator a, object::arrayType::iterator b);
object::objectPtr ArrayResize(object::objectPtr obj, object::arrayType& args);

object::objectPtr ArrayIterator (object::objectPtr obj, object::arrayType& args);
object::objectPtr ArrayIteratorGet (object::objectPtr obj, object::arrayType& args);
object::objectPtr ArrayIteratorDistance (object::objectPtr obj, object::arrayType& args);
object::objectPtr ArrayIteratorReferenceAssignOperator (object::objectPtr obj, object::arrayType& args);

#endif
