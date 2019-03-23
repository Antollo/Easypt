# `parse`

#### `..Root.parse`

Parses code from string to `BlockCallable` object. It is used by `import` and `-file` flag.

* **Parameters:** `String`

* **Return value:** `BlockCallable`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:

```c
auto fun.=(parse("basicOut(\"from string\");"));
fun();
```

#### Expected output:

```
from string
```