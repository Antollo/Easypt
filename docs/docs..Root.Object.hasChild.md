# `hasChild`

#### `..Root.Object.hasChild`

Checks if this object has child (member, note: variables are treated as tree nodes) named mem.

* **Parameters:** `String` mem

* **Return value:** new `Boolean`

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var mother;
mother.var son;
basicOut(mother.hasChild("son"));
```