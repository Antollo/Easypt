#ifndef CORE_H
#define CORE_H

#include <fstream>
#include "nobject.h"
#include "parser.h"

object::objectPtr apply (object::objectPtr obj, object::arrayType& args);
object::objectPtr call (object::objectPtr obj, object::arrayType& args);
object::objectPtr Exception (object::objectPtr obj, object::arrayType& args);
object::objectPtr except (object::objectPtr obj, object::arrayType& args);
object::objectPtr copy (object::objectPtr obj, object::arrayType& args);
object::objectPtr parse (object::objectPtr obj, object::arrayType& args);
object::objectPtr basicOut (object::objectPtr obj, object::arrayType& args);
object::objectPtr import (object::objectPtr obj, object::arrayType& args);
object::objectPtr instanceOf (object::objectPtr obj, object::arrayType& args);

#endif // CORE_H
