# `getChild`

#### `..Root.Object.getChild`

Returns child (member, note: variables are treated as tree nodes) of this object named mem.

* **Parameters:** `String` mem

* **Return value:** reference to child

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto father;
father.auto son.=("I'm son");
log(father.getChild("son"));
```