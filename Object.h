#ifndef OBJECT_H
#define OBJECT_H

#include "nobject.h"

object::objectPtr Object (object::objectPtr obj, object::arrayType& args);
object::objectPtr assignOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr referenceAssignOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr ObjectCopy (object::objectPtr obj, object::arrayType& args);
object::objectPtr getParent (object::objectPtr obj, object::arrayType& args);
object::objectPtr hasParent (object::objectPtr obj, object::arrayType& args);
object::objectPtr getChild (object::objectPtr obj, object::arrayType& args);
object::objectPtr removeChild (object::objectPtr obj, object::arrayType& args);
object::objectPtr getChildrenArray (object::objectPtr obj, object::arrayType& args);
object::objectPtr hasChild (object::objectPtr obj, object::arrayType& args);
object::objectPtr addChild1 (object::objectPtr obj, object::arrayType& args);
object::objectPtr addChild2 (object::objectPtr obj, object::arrayType& args);
object::objectPtr getName (object::objectPtr obj, object::arrayType& args);
object::objectPtr setName (object::objectPtr obj, object::arrayType& args);
object::objectPtr notEqualOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr equalReferenceOperator (object::objectPtr obj, object::arrayType& args);
//object::objectPtr equalSignaturesTypeOperator (object::objectPtr obj, object::arrayType& args);
//object::objectPtr equalInternalTypeOperator (object::objectPtr obj, object::arrayType& args);
object::objectPtr debugTree (object::objectPtr obj, object::arrayType& args);

#endif
