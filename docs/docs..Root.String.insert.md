# `insert`

#### `..Root.String.insert`

Inserts a copy of the sequence of characters in the range [first, last) before element pointed by w.

* **Parameters:** `StringIterator` w, `StringIterator` first, `StringIterator` last

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var a.=("----");
var b.=("||");
a.insert(a.begin().+(2), b.begin(), b.end());
basicOut(a);
```

#### Expected output:

    --||--
