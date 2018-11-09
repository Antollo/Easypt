# `erase`

#### `..Root.Array.erase`

Erases the sequence of elements in the range [first, last).

* **Parameters:** `ArrayIterator` first, `ArrayIterator` last

* **Return value:** reference to this `Array`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");

arr.erase(arr.begin(), arr.begin().+(2));
basicOut(arr);
```
