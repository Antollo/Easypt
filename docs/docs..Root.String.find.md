# `find`

#### `..Root.String.find`

Searches the string for the first occurrence of str, the search only includes characters at or after position pos.

* **Parameters:** `String` str, `Int` pos

* **Return value:** new `Int`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
basicOut("Hello World".find("lo", 0));

var str.=("Hello World!");
var begin.=(str.begin().+(str.find(" ", 0)));
var end.=(str.begin().+(str.find("!", 0)));
str.erase(begin, end);
basicOut(str);
```

#### Expected output:

    3
    Hello!

