#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef INTERFACE
#include <stdarg.h>
typedef void object;
#define EXTERN extern

#else

#include <iostream>
#include <string>
#include <cstdarg>
#include "nobject.h"
#define EXTERN  extern "C"
#endif

EXTERN int getInt(object* obj);
EXTERN void setInt(object* obj, int i);
EXTERN double getDouble(object* obj);
EXTERN void setDouble(object* obj, double d);
EXTERN const char* getString(object* obj);
EXTERN void setString(object* obj, const char* s);
EXTERN void* getVoidPtr(object* obj);
EXTERN void setVoidPtr(object* obj, void* v);

EXTERN object* ezRead(object* obj, const char* name);
EXTERN object* ezReadRecursive(object* obj, const char* name);
EXTERN object* ezVar(object* obj, const char* name);
EXTERN object* ezCall(object* obj, ...);

#endif
