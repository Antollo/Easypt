# `distance`

#### `..Root.ArrayIterator.distance`

Gets distance from another iterator as new `Int`.

* **Parameters:** another `ArrayIterator` 

* **Return value:** new `Int`

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");
basicOut(arr.begin().distance(arr.end()));
```