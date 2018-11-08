# `NotSupportedOnThisOSException`

#### `..Root.NotSupportedOnThisOSException`

Constructs new `NotSupportedOnThisOSException` which is thrown when trying to do something not supported on current operating system.

* **Parameters:** any number of `String` type variables

* **Return value:** new `NotSupportedOnThisOSException`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
if (mysteriousCondition, {
    throw(NotSupportedOnThisOSException("Not supported!"));
});
```