# `for`

#### `..Root.BlockCallable.for`

While `compare(someValue)` is true call block and then change.

```c
for (compare, someValue, change, block);
```

* **Parameters:** `Callable` compare, someValue of any type, `Callable` change,  `Callable` block

* **Return value:** last result of calling block (or empty object if there was no call)

## Child of:

[`BlockCallable`](docs..Root.BlockCallable.md)

## Signatures:

`NativeCallable`, `Callable`

## Examples:

```c
for (auto i.=(0).<, 10, i.++, {
    log(i);
});
```

```c
auto arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (auto it.=(arr.begin()).!=, arr.end(), it.++, {
    log(it.get());
});
```

```c
auto str.=("Hello world!");
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    log(it.get());
});
```
