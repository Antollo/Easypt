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
auto str.=("Hello World!");
log(str.readOperator(6).get());
log(str[6].get());
```