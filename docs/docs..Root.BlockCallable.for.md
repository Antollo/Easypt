# `for`

#### `..Root.BlockCallable.for`

While `comperator(someValue)` is true call block and then change.

```c
for (comparator, someValue, change, block);
```

* **Parameters:** `Callable` comparator, someValue of any type, `Callable` change,  `Callable` block

* **Return value:** reference to block

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Examples:

```c
for (var i.=(0).<, 10, i.++, {
    basicOut(i);
});
```

```c
var arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (var it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```

```c
var str.=("Hello world!");
for (var it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```
