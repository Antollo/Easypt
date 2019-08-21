# `readOperator`

#### `..Root.Array.readOperator`

Returns iterator pointing to i-th element. Read operator (`[]`) is shorthand for this function.

* **Parameters:** `Int` i

* **Return value:** new `ArrayIterator`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");
log(arr[1].get());
```