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

auto str.=("\122\123\124");
auto a.=(ByteView(str));

for (auto it.=(a.begin()).!=, a.end(), it.++, {
    basicOut(it.get().toInt());
});
```

#### Expected output:

```
122
123
124
```