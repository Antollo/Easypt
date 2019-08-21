# `end`

#### `..Root.Array.end`

Returns an iterator pointing after the last element of this `Array`.

* **Return value:** new `ArrayIterator`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (auto it.=(arr.begin()).!=, arr.end(), it.++, {
    log(it.get());
});
```