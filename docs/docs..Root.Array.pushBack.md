# `pushBack`

#### `..Root.Array.pushBack`

Appends given variables to array (as references).

* **Parameters:** any number of variables

* **Return value:** reference to this `Array`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (auto it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```