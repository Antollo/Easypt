# `+`

#### `..Root.StringIterator.+`

Returns new `StringIterator` moved forward by arguments value;

* **Parameters:** `Int`

* **Return value:** new `StringIterator`

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