# `>`

#### `..Root.ArrayIterator.>`

Checks if this `ArrayIterator` is pointing after another `ArrayIterator`. This operation makes sense only if both iterators are pointing to the same `Array`

* **Parameters:** another `ArrayIterator`

* **Return value:** new `Boolean`

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var arr.=(Array());
arr.pushBack("abc", "def");
basicOut(arr.begin().>(arr.end()));
```