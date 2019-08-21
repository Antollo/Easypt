# `NativeFunction`

#### `..Root.NativeFunction`

Constructs new `NativeFunction`, extract exported function from given `NativeInterface`.

Exported functions should be of following type.

```c
object* functionName(object* obj, object** args, int i)
```

> TODO: More documentation

* **Parameters:** `NativeInterface` interface, `String` function name

* **Return value:** new `NativeFunction`

### `NativeFunction` type signatures:

`NativeFunction`, `Object`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`callOperator`](docs..Root.NativeFunction.callOperator.md)

## Example:

_**Note:** There is no difference between_

```
auto functionName.=(interface["functionName"]);
```

_and_

```
auto functionName.=(NativeFunction(interface, "functionName"));
```

```c
import("nativeInterface");

var interface.=(NativeInterface("
    #include <stdio.h>
    #include <interface.h>

    object* promptInt(object* obj, object** args, int size)
    { 
        printf(\"Old value is: %i \\nType in new value: \", getInt(args[0]));
        int input;
        scanf(\"%i\", &input);
        setInt(args[0], input);
        printf(\"New value is: %i \\n\", getInt(args[0]));
        return obj;
    }

    object* createString(object* obj, object** args, int size)
    { 
        object* String = readRecursive(obj, \"String\");
        object* newString = call(String, NULL);
        setString(newString, \"new string value\");
        return newString;
    }

    object* callbackForEach(object* obj, object** args, int size)
    {
        for (int i = 1; i < size; i++)
        {
            call(args[0], args[i], NULL);
        }
        return obj;
    }

    object* returnlog(object* obj, object** args, int size)
    {
        object* log = readRecursive(obj, \"log\");
        return log;
    }
"));

auto integer.=(7);

auto promptInt.=(interface["promptInt"]);
log(promptInt(integer));

auto createString.=(NativeFunction(interface, "createString"));
log(createString());

auto callbackForEach.=(interface["callbackForEach"]);
callbackForEach(log, 1, 2.3, "abc");

auto returnlog.=(NativeFunction(interface, "returnlog"));
returnlog()(4, 5.6, "defg");
```

#### Possible output:

```
Old value is: 7
Type in new value: 2
New value is: 2
new string value
1
2.3
abc
4
5.6
defg
```