# `begin`

#### `..Root.Array.begin`

Returns an iterator pointing to the first element of this `Array`.

* **Return value:** new `ArrayIterator`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (var it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```
