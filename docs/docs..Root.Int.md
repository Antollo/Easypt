# `Int`

#### `..Root.Int`

Constructs new `Int`.

* **Return value:** new `Int` of value `0`

### `Int` type signatures:

`Object`, `Basic`, `Int`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- `toString` converts integer to string, returns new `String` 
- `toInt` equivalent of `copy`
- `toDouble` converts integer to floating point number, returns new `Double`
- `toBoolean` converts integer to logical value, returns new `Boolean`
- `++` increments this object, returns reference to this object
- `--` decrements this object, returns reference to this object
- `==` compares integers, returns new `Boolean`
- `+` adds two floating point numbers, returns new `Int`
- `-` subtracts one integer from another, returns new `Int`
- `>` compares two integers, returns new `Boolean`
- `<` compares two integers, returns new `Boolean`
- `>=` compares two integers, returns new `Boolean`
- `<=` compares two integers, returns new `Boolean`
- `&` performs bitwise and
- `|` performs bitwise or
- `^` performs bitwise xor
- `~` performs bitwise not
- `*` multiplies two integers, returns new `Int`
- `/`  divides integer by another, returns new `Int`
- `%` computes remainders of division of two integers, returns new `Int`

## Example:

```c
auto n.=(10);
auto str.=(String());
auto conditon.=(n.toBoolean());
while(conditon, {
    str.pushBack("a");
    conditon.=(n.--().toBoolean());
});
basicOut(str);
```