# `Array`

#### `..Root.Array`

Constructs new `Array`. `Array` is a sequence container that encapsulates dynamic size arrays.

1. Constructs an empty array.

2. Constructs a array filled with n consecutive copies of empty `Object`.

3. Constructs a array filled with n consecutive copies of c.

* **Parameters:**

    1. _no parameters_
    2. `Int` n
    3. `Int` n, any c

* **Return value:** new `Array`

### `Object` type signatures:

`Object`, `Container`, `Iterable`, `Array`

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
- [`insert`](docs..Root.Array.insert.md)
- [`erase`](docs..Root.Array.erase.md)
- [`pushBack`](docs..Root.Array.pushBack.md)

## Example:

```c
var arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (var it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```

