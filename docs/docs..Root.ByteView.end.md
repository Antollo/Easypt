# `end`

#### `..Root.ByteView.end`

Returns an iterator pointing after the last byte of this `ByteView`.

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