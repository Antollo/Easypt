# `resize`

#### `..Root.String.resize`

Resizes the string to a length of n characters. If n is smaller than the current string length, the current value is shortened to its first n character, removing the characters beyond the n-th. If n is greater than the current string length, the current content is extended by inserting at the end as many characters as needed to reach a size of n.

* **Parameters:** `Int` n, `String` character

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:



```c
auto str.=("Hello World!");
log(str.resize(5, "!"));
str.=("Hello World!");
log(str.resize(20, "!"));
```

#### Expected output:

    Hello
    Hello World!!!!!!!!!