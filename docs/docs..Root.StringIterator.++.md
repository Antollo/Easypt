# `++`

#### `..Root.StringIterator.++`

Increments `StringIterator` instance (equivalent of `parent.=(parent.+(1))`).

* **Return value:** reference to this (incremented) `StringIterator` 

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var str.=("Hello world!");
for (var it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```