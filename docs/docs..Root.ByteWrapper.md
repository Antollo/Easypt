# `ByteWrapper`

#### `..Root.ByteWrapper`

Constructs a new `ByteWrapper` (also used for internal `ByteViewIterator.get()` purposes). For creating `ByteWrapper` pointing to data use `ByteViewIterator.get()` or this constructor.

`ByteWrapper` wraps real in-memory byte and allows to manipulate that bound byte.

* **Parameters:** `Int`

* **Return value:** new `ByteWrapper` (pointing to least significant byte of given integer)

### `ArrayIterator` type signatures:

`Object`, `Iterator`, `ArrayIterator` 

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- [`toInt`](docs..Root.ByteWrapper.toInt.md)
- [`|=`](docs..Root.ByteWrapper.or=.md)
- [`&=`](docs..Root.ByteWrapper.&=.md)
- [`^=`](docs..Root.ByteWrapper.^=.md)
- [`<<=`](docs..Root.ByteWrapper.<<=.md)
- [`>>=`](docs..Root.ByteWrapper.>>=.md)
- [`~=`](docs..Root.ByteWrapper.~=.md)

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