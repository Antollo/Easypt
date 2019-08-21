# `throw`

#### `..Root.BlockCallable.throw`

Throws an exception. _[Longer description will come.]_

* **Parameters:** variable of any type, preferably kind of `Exception`

* **Return value:** _none_

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
try({
    throw(Exception("Error!"));
}, {
    log(args[0].get());
});
```