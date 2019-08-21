# `get`

#### `..Root.ArrayIterator.get`

Gets reference to element pointed by iterator.

* **Return value:** reference to any type

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");
for (auto it.=(arr.begin()).!=, arr.end(), it.++, {
    log(it.get());
});
```