# `ByteView`

#### `..Root.ByteView`

Constructs new `ByteView`. `ByteView` is a sequence container providing an interface for accessing bytes of variables.

* **Parameters:** `Int`, `Double`, `Boolean` or `String`

* **Return value:** new `ByteView`

### `ByteView` type signatures:

`Object`, `Container`, `Iterable`, `ByteView`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`begin`](docs..Root.ByteView.begin.md)
- [`end`](docs..Root.ByteView.end.md)
- [`==`](docs..Root.ByteView.==.md)
- [`readOperator`](docs..Root.ByteView.readOperator.md)
- [`size`](docs..Root.ByteView.size.md)

## Example:

```c
import("memory");
import("algorithm");

var a.=(ByteView("abcd"));
var b.=(ByteView(1684234849));

basicOut(a.==(b), "");

algorithm.forEach(a, {
    basicOut(args[0].get().toInt());
});

basicOut("");

algorithm.forEach(b, {
    basicOut(args[0].get().toInt());
});
```

#### Expected output:

```
true

97
98
99
100

97
98
99
100
```