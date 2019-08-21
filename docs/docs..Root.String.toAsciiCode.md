# `toAsciiCode`

#### `..Root.String.toAsciiCode`

Converts first character of string to integer (following ASCII code).

* **Return value:** new `Int`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:

```c
auto str.=("abc");
log(str[0].get().toAsciiCode());
```

#### Expected output:

```
97
```