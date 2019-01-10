# `String`

#### `..Root.String`

1. Constructs an empty `String`.

2. Constructs a string filled with n consecutive copies of character c.

* **Parameters:**

    1. _no parameters_
    2. `Int` n, `String` c

* **Return value:** new `String`

### `String` type signatures:

`Object`, `Basic`, `String`, `Iterable`, `Container`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:
- [`toString`](docs..Root.String.toString.md)
- [`toInt`](docs..Root.String.toInt.md)
- [`toDouble`](docs..Root.String.toDouble.md)
- [`toBoolean`](docs..Root.String.toBoolean.md)
- [`toAsciiCode`](docs..Root.String.toAsciiCode.md)
- [`begin`](docs..Root.String.begin.md)
- [`end`](docs..Root.String.end.md)
- [`==`](docs..Root.String.==.md)
- [`readOperator`](docs..Root.String.readOperator.md)
- [`size`](docs..Root.String.size.md)
- [`find`](docs..Root.String.find.md)
- [`replace`](docs..Root.String.replace.md)
- [`replaceAll`](docs..Root.String.replaceAll.md)
- [`empty`](docs..Root.String.empty.md)
- [`resize`](docs..Root.String.resize.md)
- [`clear`](docs..Root.String.clear.md)
- [`substring`](docs..Root.String.substring.md)
- [`insert`](docs..Root.String.insert.md)
- [`erase`](docs..Root.String.erase.md)
- [`pushBack`](docs..Root.String.pushBack.md)
- [`+`](docs..Root.String.+.md)
- `>` compares two strings, returns new `Boolean`
- `<` compares two strings, returns new `Boolean`
- `>=` compares two strings, returns new `Boolean`
- `<=` compares two strings, returns new `Boolean`


## Example:



```c
basicOut(String().size());
basicOut(String(3, "a"));
```