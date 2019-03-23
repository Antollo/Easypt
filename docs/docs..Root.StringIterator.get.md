# `get`

#### `..Root.StringIterator.get`

Gets value of an element (new `String` consisting of one character) pointed by iterator.

* **Return value:** new `String` of size 1

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto str.=("Hello world!");
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```