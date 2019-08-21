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

auto str.=("\122\123\124");
auto a.=(ByteView(str));

for (auto it.=(a.begin()).!=, a.end(), it.++, {
    log(it.get().toInt());
});
```

#### Expected output:

```
122
123
124
```