# `readOperator`

#### `..Root.String.readOperator`

Returns iterator pointing to i-th character. Read operator (`[]`) is shorthand for this function.

* **Parameters:** `Int` i

* **Return value:** new `StringIterator`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var str.=("Hello World!");
basicOut(str.readOperator(6).get());
basicOut(str[6].get());
```