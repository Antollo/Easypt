# `erase`

#### `..Root.String.erase`

Erases the sequence of characters in the range [first, last).

* **Parameters:** `StringIterator` first, `StringIterator` last

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:



```c
var str.=("Hello World!");
var begin.=(str.begin().+(str.find(" ", 0)));
var end.=(str.begin().+(str.find("!", 0)));
str.erase(begin, end);
basicOut(str);
```

#### Expected output:

    Hello!

