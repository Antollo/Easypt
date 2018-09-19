#ifndef STRING__H
#define STRING__H

#include "nobject.h"

object::objectPtr String (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToString (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToInt (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToDouble (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringToBoolean (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringReadOperator (object::objectPtr obj, object::argsContainer& args);

object::objectPtr StringIterator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorGet (object::objectPtr obj, object::argsContainer& args);
object::objectPtr StringIteratorReferenceAssignOperator (object::objectPtr obj, object::argsContainer& args);

#endif
