# `end`

#### `..Root.String.end`

Returns an iterator pointing after the last character of this `String`.

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