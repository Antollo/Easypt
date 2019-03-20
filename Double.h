#ifndef DOUBLE_H
#define DOUBLE_H

#include "nobject.h"

object::objectPtr Double (object::objectPtr obj, object::arrayType& args);
object::objectPtr DoubleToString (object::objectPtr obj, object::arrayType& args);
object::objectPtr DoubleToInt (object::objectPtr obj, object::arrayType& args);
object::objectPtr DoubleToDouble (object::objectPtr obj, object::arrayType& args);
object::objectPtr DoubleToBoolean (object::objectPtr obj, object::arrayType& args);

#endif
