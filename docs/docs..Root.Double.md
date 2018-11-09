# `Double`

#### `..Root.Double`

Constructs new `Double`.

* **Return value:** new `Double` of value `0.0`

### `Double` type signatures:

`Object`, `Basic`, `Double`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- `toString` converts floating point number to string, returns new `String` 
- `toInt` converts floating point number to integer, returns new `Int`
- `toDouble` equivalent of `copy`
- `toBoolean` converts floating point number to logical value, returns new `Boolean`
- `++` increments this object, returns reference to this object
- `--` decrements this object, returns reference to this object
- `==` compares two floating point numbers, returns new `Boolean`
- `+` adds two floating point numbers, returns new `Double`
- `-` subtracts one floating point number from another, returns new `Double`
- `>` compares two floating point numbers, returns new `Boolean`
- `<` compares two floating point numbers, returns new `Boolean`
- `>=` compares two floating point numbers, returns new `Boolean`
- `<=` compares two floating point numbers, returns new `Boolean`
- `*` multiplies two floating point numbers, returns new `Double`
- `/`  divides one floating point number by another, returns new `Double`

## Example:

```c
basicOut(13.0./(7.0));
```