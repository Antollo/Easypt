# `begin`

#### `..Root.String.begin`

Returns an iterator pointing to the first character of the string.

* **Return value:** new `StringIterator`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var str.=("Hello world!");
for (var it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```