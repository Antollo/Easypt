# `replaceAll`

#### `..Root.String.replaceAll`

Replaces all occurrences of a with b.

* **Parameters:** `String` a, `String` b

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:

```c
auto str.=("a aa aaa");
str.replaceAll("a", "b");
basicOut(str);
```