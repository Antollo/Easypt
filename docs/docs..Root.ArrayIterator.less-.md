# `<-`

#### `..Root.ArrayIterator.<-`

Change reference on position pointed by this `ArrayIterator` to reference to another object.

* **Parameters:** variable of any type

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var a.=("a");
var b.=("b");
var arr.=(Array());
arr.pushBack(a, b);
basicOut(a, b, arr, "\n");

arr.[0].<-("c");
arr.[1].get().=("d");
basicOut(a, b, arr);
```

#### Expected output:

```
a
b
a
b


a
d
c
d
```