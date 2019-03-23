# `<=`

#### `..Root.StringIterator.<=`

Checks if this `StringIterator` is pointing before or to the same element as another `StringIterator`. This operation makes sense only if both iterators are pointing to the same `String`

* **Parameters:** another `StringIterator`

* **Return value:** new `Boolean`

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto str.=("Hello World!");
auto a.=(str.begin().+(str.find("e", 0)));
auto b.=(str.begin().+(str.find("d", 0)));

basicOut(a.<=(b));
```

#### Expected output:

```
true
```