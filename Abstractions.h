#ifndef ABSTRACTIONS_H
#define ABSTRACTIONS_H

#include "nobject.h"

object::objectPtr Basic (object::objectPtr obj, object::argsContainer& args);
object::objectPtr Iterable (object::objectPtr obj, object::argsContainer& args);
object::objectPtr Iterator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr Container (object::objectPtr obj, object::argsContainer& args);

#endif
