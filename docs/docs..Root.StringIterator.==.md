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
auto str.=("Hello world!");
auto x.=(str.begin().+(4));
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    if (it.==(x), { basicOut(it.get()) });
});
```