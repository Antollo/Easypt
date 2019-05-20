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

EXTERN object* readNormal(object* obj, const char* name);
EXTERN object* readRecursive(object* obj, const char* name);
EXTERN object* var(object* obj, const char* name);
EXTERN object* call(object* obj, ...);

#endif
