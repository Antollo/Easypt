# `=`

#### `..Root.Object.=`

Assign another object to this object (parent and name of this object do not change).

* **Parameters:** object of any type

* **Return value:** reference to this object

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var a.=(5);
var b.=("abc");
a.=(b);
basicOut(a, b);
```
