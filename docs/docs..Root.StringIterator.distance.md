# `distance`

#### `..Root.StringIterator.distance`

Gets distance from another iterator as new `Int`.

* **Parameters:** another `StringIterator` 

* **Return value:** new `Int`

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var str.=("Hello world!");
basicOut(str.begin().distance(str.end()));
```