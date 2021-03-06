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
auto a.=("a");
auto b.=("b");
auto arr.=(Array());
arr.pushBack(a, b);
log(a, b, arr, "\n");

arr.[0].<-("c");
arr.[1].get().=("d");
log(a, b, arr);
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