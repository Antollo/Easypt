# `removeChild`

#### `..Root.Object.removeChild`

Remove this object's child (member, note: variables are treated as tree nodes) named mem.

* **Parameters:** `String` mem

* **Return value:** reference to this `Object`

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto mother;
mother.auto son;
mother.removeChild("son");
```