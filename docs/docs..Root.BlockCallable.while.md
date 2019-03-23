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
auto condition.=(true);
auto i.=(0);
while(condition, {
    basicOut(i.++());
    if(i.==(10), { condition.=(false); });
});
```

---

```c
auto a.=(6);
auto b.=(9);
auto condition.=(a.!=(b));
basicOut(while (condition, {
    if (a.>(b), { a.=(a.-(b)); });
    if (b.>(a), { b.=(b.-(a)); });
    condition.=(a.!=(b));
    return (a);
}));
```