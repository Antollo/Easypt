# `NativeInterface`

#### `..Root.NativeInterface`

Compile C source code from string to memory.

> TODO: More documentation

You might include 

```c
typedef void object;

int getInt(object* obj);
void setInt(object* obj, int i);
double getDouble(object* obj);
void setDouble(object* obj, double d);
const char* getString(object* obj);
void setString(object* obj, const char* s);
void* getVoidPtr(object* obj);
void setVoidPtr(object* obj, void* v);

object* ezRead(object* obj, const char* name);
object* ezReadRecursive(object* obj, const char* name);
object* ezVar(object* obj, const char* name);
object* ezCall(object* obj, ...);
```

* **Parameters:** 

* **Return value:**

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeInterface`, `Object`

## Members:

- [`debugTree`](docs..Root.nativeInterface.debugTree.md)
- [`=`](docs..Root.nativeInterface.=.md)
- [`getParent`](docs..Root.nativeInterface.getParent.md)
- [`getChild`](docs..Root.nativeInterface.getChild.md)
- [`getChildrenArray`](docs..Root.nativeInterface.getChildrenArray.md)
- [`hasChild`](docs..Root.nativeInterface.hasChild.md)
- [`removeChild`](docs..Root.nativeInterface.removeChild.md)
- [`addChild`](docs..Root.nativeInterface.addChild.md)
- [`getName`](docs..Root.nativeInterface.getName.md)
- [`setName`](docs..Root.nativeInterface.setName.md)
- [`copy`](docs..Root.nativeInterface.copy.md)
- [`!=`](docs..Root.nativeInterface.!=.md)
- [`===`](docs..Root.nativeInterface.===.md)
- [`readOperator`](docs..Root.nativeInterface.readOperator.md)


## Example:





