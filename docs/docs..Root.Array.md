# `Array`

#### `..Root.Array`

* **Parameters:**

* **Return value:**

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`==`](docs..Root.Array.==.md)
- [`begin`](docs..Root.Array.begin.md)
- [`end`](docs..Root.Array.end.md)
- [`readOperator`](docs..Root.Array.readOperator.md)
- [`size`](docs..Root.Array.size.md)
- [`resize`](docs..Root.Array.resize.md)
- [`pushBack`](docs..Root.Array.pushBack.md)


## Example:

```c
var arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (var it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```

