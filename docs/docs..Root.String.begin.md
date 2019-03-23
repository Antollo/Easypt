# `begin`

#### `..Root.String.begin`

Returns an iterator pointing to the first character of this `String`.

* **Return value:** new `StringIterator`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto str.=("Hello world!");
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```