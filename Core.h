#ifndef CORE_H
#define CORE_H

#include <fstream>
#include "nobject.h"
#include "parser.h"

object::objectPtr Exception (object::objectPtr obj, object::argsContainer& args);
object::objectPtr parse (object::objectPtr obj, object::argsContainer& args);
object::objectPtr basicOut (object::objectPtr obj, object::argsContainer& args);
object::objectPtr import (object::objectPtr obj, object::argsContainer& args);

#endif // CORE_H
