#ifndef STRING__H
#define STRING__H

#include "nobject.h"

object::objectPtr String (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToString (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToInt (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToDouble (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToBoolean (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringBegin (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringEnd (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringReadOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringSize (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringEqualOperator (object::objectPtr obj, object::argsContainer& args);

object::objectPtr StringIterator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorIncrement (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorDecrement (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorGet (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorEqualOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorAssignOperator (object::objectPtr obj, object::argsContainer& args);

#endif
