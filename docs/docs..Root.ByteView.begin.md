# `begin`

#### `..Root.ByteView.begin`

Returns an iterator pointing to the first byte of this `ByteView`.

* **Return value:** new `ByteViewIterator`

## Child of:

[`ByteView`](docs..Root.ByteView.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("memory");

var str.=("\122\123\124");
var a.=(ByteView(str));

for (var it.=(a.begin()).!=, a.end(), it.++, {
    basicOut(it.get().toInt());
});
```

#### Expected output:

```
122
123
124
```