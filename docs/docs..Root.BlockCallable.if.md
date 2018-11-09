# `if`

#### `..Root.BlockCallable.if`

1. If condition is true call if-block.

2. If condition is true call if-block, else call else-block.

* **Parameters:**

    1. `Basic` (best choice is `Boolean`) condition, `Callable` if-block
    2. `Basic` (best choice isr `Boolean`) condition, `Callable` if-block, `Callable` else-block

* **Return value:** reference to condition

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var a.=(6);
var b.=(9);
if (a.>(b), {
    basicOut("a is greater than b");
}, {
    basicOut("a is less or equal than b");
});
```