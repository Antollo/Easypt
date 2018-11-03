# `String`

#### `..Root.String`

1. Constructs an empty `String`.

2. Constructs a string filled with n consecutive copies of character c.

* **Parameters:**
    1. _no parameters_
    2. `Int` n, `String` c

* **Return value:** new `String`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`==`](docs..Root.String.==.md)
- [`toString`](docs..Root.String.toString.md)
- [`toInt`](docs..Root.String.toInt.md)
- [`toDouble`](docs..Root.String.toDouble.md)
- [`toBoolean`](docs..Root.String.toBoolean.md)
- [`begin`](docs..Root.String.begin.md)
- [`end`](docs..Root.String.end.md)
- [`readOperator`](docs..Root.String.readOperator.md)
- [`size`](docs..Root.String.size.md)
- [`find`](docs..Root.String.find.md)
- [`empty`](docs..Root.String.empty.md)
- [`resize`](docs..Root.String.resize.md)
- [`clear`](docs..Root.String.clear.md)
- [`substring`](docs..Root.String.substring.md)
- [`insert`](docs..Root.String.insert.md)
- [`erase`](docs..Root.String.erase.md)
- [`+`](docs..Root.String.+.md)

## Example:

```c
basicOut(String().size());
basicOut(String(3, "a"));
```