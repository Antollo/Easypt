# `while`

#### `..Root.BlockCallable.while`

While condition is true call block.

* **Parameters:** `Basic` condition, `Callable` block

* **Return value:** last result of calling block (or empty object if there was no call)

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Examples:

```c
var condition.=(true);
var i.=(0);
while(condition, {
    basicOut(i.++());
    if(i.==(10), { condition.=(false); });
});
```

---

```c
var a.=(6);
var b.=(9);
var condition.=(a.!=(b));
basicOut(while (condition, {
    if (a.>(b), { a.=(a.-(b)); });
    if (b.>(a), { b.=(b.-(a)); });
    condition.=(a.!=(b));
    return (a);
}));
```