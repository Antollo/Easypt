# `--`

#### `..Root.StringIterator.--`

Decrements `StringIterator` instance (equivalent of `parent.=(parent.-(1))`).

* **Return value:** reference to incremented `StringIterator` instance 

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var str.=("Hello world!");
for (var it.=(str.end()).!=, str.begin(), it.--, {
    basicOut(it.-(1).get());
});
```