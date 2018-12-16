# `replace`

#### `..Root.String.replace`

Replaces the first occurrence of a with b.

* **Parameters:** `String` a, `String` b

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:

```c
var str.=("Hello World!");
str.replace("World", "there");
basicOut(str);
```