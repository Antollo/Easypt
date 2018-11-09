# `while`

#### `..Root.BlockCallable.while`

While condition is true call block.

* **Parameters:** `Basic` condition, `Callable` block

* **Return value:** reference to condition

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var condition.=(true);
var i.=(0);
while(condition, {
    basicOut(i.++());
    if(i.==(10), { condition.=(false); });
});
```