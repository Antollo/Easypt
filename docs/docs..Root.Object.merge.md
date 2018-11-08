# `merge`

#### `..Root.Object.merge`

Marges two object by copying signatures, members and internal value (real data in memory like integer or array) from arg to this `Object`.

* **Parameters:** `Object` arg 

* **Return value:** reference to this `Object`

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var a.=(Iterable());
a.debugTree();
a.merge(Container());
a.debugTree();
```