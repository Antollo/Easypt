#ifndef COMMON_H
#define COMMON_H

#include "nobject.h"
#include "parser.h"

object::objectPtr parse (object::objectPtr obj, object::argsContainer& args);
object::objectPtr errorOut (object::objectPtr obj, object::argsContainer& args);
object::objectPtr instanceOf (object::objectPtr obj, object::argsContainer& args);
object::objectPtr Null (object::objectPtr obj, object::argsContainer& args);

#endif
