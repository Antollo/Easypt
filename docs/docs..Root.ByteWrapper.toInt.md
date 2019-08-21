# `toInt`

#### `..Root.ByteWrapper.toInt`

Return byte value as integer.

* **Return value:** new `Int`

## Child of:

[`ByteWrapper`](docs..Root.ByteWrapper.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("memory");
import("algorithm");

auto str.=("\012\012\012\012\012\012");
auto a.=(ByteView(str));

a[0].get().|=(ByteWrapper(6));
a[1].get().&=(ByteWrapper(6));
a[2].get().^=(ByteWrapper(6));
a[3].get().<<=(ByteWrapper(1));
a[4].get().>>=(ByteWrapper(1));
a[5].get().~=();


algorithm.forEach(a, {
    log(args[0].get().toInt());
});
```

#### Expected output

```
14
4
10
24
6
243
```