#ifndef OBJECT_H
#define OBJECT_H

#include "nobject.h"

object::objectPtr Object (object::objectPtr obj, object::argsContainer& args);
object::objectPtr assignOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr merge (object::objectPtr obj, object::argsContainer& args);
object::objectPtr destructor (object::objectPtr obj, object::argsContainer& args);
object::objectPtr copy (object::objectPtr obj, object::argsContainer& args);
object::objectPtr getParent (object::objectPtr obj, object::argsContainer& args);
object::objectPtr hasParent (object::objectPtr obj, object::argsContainer& args);
object::objectPtr getChild (object::objectPtr obj, object::argsContainer& args);
object::objectPtr hasChild (object::objectPtr obj, object::argsContainer& args);
object::objectPtr addChild1 (object::objectPtr obj, object::argsContainer& args);
object::objectPtr addChild2 (object::objectPtr obj, object::argsContainer& args);
object::objectPtr getName (object::objectPtr obj, object::argsContainer& args);
object::objectPtr instanceOf (object::objectPtr obj, object::argsContainer& args);
object::objectPtr notEqualOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr equalReferenceOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr equalSignaturesTypeOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr equalInternalTypeOperator (object::objectPtr obj, object::argsContainer& args);
object::objectPtr debugTree (object::objectPtr obj, object::argsContainer& args);

#endif
