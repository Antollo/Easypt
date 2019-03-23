# `--`

#### `..Root.StringIterator.--`

Decrements `StringIterator` instance (equivalent of `it.=(it.-(1))`).

* **Return value:** reference to this (decremented) `StringIterator` 

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:

```c
auto str.=("Hello world!");
for (auto it.=(str.end()).!=, str.begin(), it.--, {
    basicOut(it.-(1).get());
});
```