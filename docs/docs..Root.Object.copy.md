# `copy`

#### `..Root.Object.copy`

Makes copy of this object (signatures, children, internal value).

* **Return value:** new object (e.g `String` or `ArrayIterator`)

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto a.=(5);
basicOut(a.copy().++());
basicOut(a)
```

#### Expected output:

```
6
5
```