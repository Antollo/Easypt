# `++`

#### `..Root.ArrayIterator.++`

Increments `ArrayIterator` instance (equivalent of `it.=(it.+(1))`).

* **Return value:** reference to this (increments) `ArrayIterator`

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