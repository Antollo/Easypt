#ifndef INT_H
#define INT_H

#include "nobject.h"

object::objectPtr Int (object::objectPtr obj, object::argsContainer& args);
object::objectPtr IntToString (object::objectPtr obj, object::argsContainer& args);
object::objectPtr IntToInt (object::objectPtr obj, object::argsContainer& args);
object::objectPtr IntToDouble (object::objectPtr obj, object::argsContainer& args);
object::objectPtr IntToBoolean (object::objectPtr obj, object::argsContainer& args);
object::objectPtr IntEqualOperator (object::objectPtr obj, object::argsContainer& args);

#endif
