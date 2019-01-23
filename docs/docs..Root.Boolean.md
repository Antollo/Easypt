# `Boolean`

#### `..Root.Boolean`

Constructs new `Boolean`.

* **Return value:** new `Boolean` of value `false`

### `Boolean` type signatures:

`Object`, `Basic`, `Boolean`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- `toString` converts logical value to string, returns new `String` 
- `toInt` converts logical value to integer, returns new `Int`
- `toDouble` converts logical value to floating point number, returns new `Double`
- `toBoolean` equivalent of `copy`
- `==` compares two logical values, returns new `Boolean`
- `!` negates value of this, returns new `Boolean`
- `&&` performs logical and, returns new `Boolean`
- `||` performs logical or, returns new `Boolean`

## Example:

```c
basicOut(true, false, "a".==("a"));
```