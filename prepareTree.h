#ifndef PREPARETREE_H
#define PREPARETREE_H

#include "Common.h"
#include "nobject.h"
#include "String_.h"
#include "Object.h"
#include "Abstractions.h"
#include "Int.h"
#include "Double.h"
#include "Boolean.h"
#include "Array.h"
#include "BlockCallable.h"
#include <utility>

std::pair<object::objectPtr, object::objectPtr> prepareTree();

#endif // PREPARETREE_H
