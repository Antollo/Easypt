# `==`

#### `..Root.StringIterator.==`

Checks if two instances of `StringIterator` are pointing to same element.

* **Parameters:** another `StringIterator` 

* **Return value:** new `Boolean`

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var str.=("Hello world!");
var x.=(str.begin().+(4));
for (var it.=(str.begin()).!=, str.end(), it.++, {
    if (it.==(x), { basicOut(it.get()) });
});
```