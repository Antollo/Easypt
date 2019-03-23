# `substring`

#### `..Root.String.substring`

Returns new substring that starts at character position pos and spans len characters (or until the end of the string).

* **Parameters:** `Int` pos, `Int` len

* **Return value:** new `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:



```c
auto str.=("Hello World!");
basicOut(str.substring(6, 5));
```