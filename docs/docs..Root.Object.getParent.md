# `getParent`

#### `..Root.Object.getParent`

Returns parent (note: variables are treated as tree nodes) of this object.

* **Return value:** reference to parent of this object

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto mother;
mother.auto son;
log(mother.son.getParent().hasChild("son"));
```