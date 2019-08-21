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
auto str.=("Hello world!");
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    log(it.get());
});
```