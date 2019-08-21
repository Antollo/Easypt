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
auto str.=("Hello World!");
auto begin.=(str.begin().+(str.find(" ", 0)));
auto end.=(str.begin().+(str.find("!", 0)));
str.erase(begin, end);
log(str);
```

#### Expected output:

    Hello!

