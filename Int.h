#ifndef INT_H
#define INT_H

#include "nobject.h"

object::objectPtr Int (object::objectPtr obj, object::arrayType& args);
object::objectPtr IntToString (object::objectPtr obj, object::arrayType& args);
object::objectPtr IntToInt (object::objectPtr obj, object::arrayType& args);
object::objectPtr IntToDouble (object::objectPtr obj, object::arrayType& args);
object::objectPtr IntToBoolean (object::objectPtr obj, object::arrayType& args);

#endif
