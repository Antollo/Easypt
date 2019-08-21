# `==`

#### `..Root.ArrayIterator.==`

Checks if two instances of `ArrayIterator` are pointing to same element.

* **Parameters:** another `ArrayIterator` 

* **Return value:** new `Boolean`

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("x");
log(arr.begin().==(arr.[0]));
```



