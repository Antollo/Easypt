# `size`

#### `..Root.ByteView.size`

Returns the number of bytes of the associated variable.

* **Return value:** new `Int`

## Child of:

[`ByteView`](docs..Root.ByteView.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("memory");

var i.=(1234);
var a.=(ByteView(i));

basicOut(a.size());
```

