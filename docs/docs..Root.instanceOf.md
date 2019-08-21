# `instanceOf`

#### `..Root.instanceOf`

Checks if first argument has signatures identical to names of following variables.

* **Parameters:** variable of any type, any number of variables

* **Return value:** new `Boolean`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
log(instanceOf(5, Int));
log(instanceOf(5.0, Int));
log(instanceOf(5.0, Double));
```