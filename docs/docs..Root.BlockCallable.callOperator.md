# `callOperator`

#### `..Root.BlockCallable.callOperator`

Calls `BlockCallable`, equivalent of call operator `()`.

* **Parameters:** any

* **Return value:** any

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto fun.=({ basicOut("called"); });
fun.callOperator();
```