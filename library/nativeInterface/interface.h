#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef INTERFACE
typedef void object;
#define EXTERN extern
#else

#include <iostream>
#include <string>
#include "nobject.h"
#define EXTERN  extern "C"
#endif

EXTERN int getInt(object* a);
EXTERN void setInt(object* a, int i);
EXTERN double getDouble(object* a);
EXTERN void setDouble(object* a, double d);
EXTERN const char* getString(object* a);
EXTERN void setString(object* a, const char* s);
EXTERN void* getVoidPtr(object* a);
EXTERN void setVoidPtr(object* a, void* v);

#endif
