# `=`

#### `..Root.Object.=`

Assign copy of another object to this object (parent and name of this object do not change). Easypt interpreter can optimize assignment to move operation, such optimization occurs when right operand of `=` has no parent.

* **Parameters:** object of any type

* **Return value:** reference to this object

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto a.=(5);
auto b.=("abc");
a.=(b);
basicOut(a, b);
```
