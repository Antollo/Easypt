# `return`

#### `..Root.BlockCallable.return`

1. Terminates the current `BlockCallable`.
2. Terminates the current `BlockCallable` and returns the specified value to its caller.

* **Parameters:** any

    1. _no parameters_
    2. any type

* **Return value:** 

    1. empty `Object`
    2. reference to any type

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto fun.=({
    log("a");
    log("b");
    return("c");
    log("d");
});

log(fun());
```