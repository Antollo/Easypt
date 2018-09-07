#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "nobject.h"

object::objectPtr Boolean (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BooleanToString (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BooleanToInt (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BooleanToDouble (object::objectPtr obj, object::argsContainer& args);
object::objectPtr BooleanToBoolean (object::objectPtr obj, object::argsContainer& args);

#endif
