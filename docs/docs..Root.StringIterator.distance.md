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
auto str.=("Hello world!");
log(str.begin().distance(str.end()));
```