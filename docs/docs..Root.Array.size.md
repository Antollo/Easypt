# `size`

#### `..Root.Array.size`

Returns the number of elements in the array.

* **Return value:** new `Int`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");
basicOut(arr.size());
```