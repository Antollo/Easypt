# `try`

#### `..Root.BlockCallable.try`

Calls first, if exception is thrown, calls second with thrown exception as its argument.

* **Parameters:** `Callable` first (to call), `Callable` second (to catch exception)

* **Return value:** reference to this `BlockCallable`

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
try({
    throw(Exception("Error!"));
}, {
    basicOut(args[0].get());
});
```

```c
try( {abababa;}, {
    basicOut(args[0].get());
});
```