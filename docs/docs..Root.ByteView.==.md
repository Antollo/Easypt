# `==`

#### `..Root.ByteView.==`

Compares bytes of two byte views.

* **Parameters:** another `ByteView`

* **Return value:** new `Boolean`

## Child of:

[`ByteView`](docs..Root.ByteView.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("memory");
import("algorithm");

auto a.=(ByteView("abcd"));
auto b.=(ByteView(1684234849));

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