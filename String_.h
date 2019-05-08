#ifndef STRING__H
#define STRING__H

#include <regex>
#include <iterator>
#include <algorithm>
#include "nobject.h"
#include "Common.h"

object::objectPtr String0 (object::objectPtr obj, object::arrayType& args);
object::objectPtr String2 (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringToString (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringToInt (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringToDouble (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringToBoolean (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringReplace (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringReplaceRegex (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringMatchRegex (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringSearchRegex (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringToAsciiCode (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringReadOperator (object::objectPtr obj, object::arrayType& args);

object::objectPtr StringIterator (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringIteratorGet (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringIteratorDistance (object::objectPtr obj, object::arrayType& args);
object::objectPtr StringIteratorReferenceAssignOperator (object::objectPtr obj, object::arrayType& args);

#endif
