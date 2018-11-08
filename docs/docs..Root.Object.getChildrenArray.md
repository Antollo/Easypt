# `getChildrenArray`

#### `..Root.Object.getChildrenArray`

Returns all children (members, note: variables are treated as tree nodes) of this object stored in array of references.

* **Return value:** new `Array`

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable

## Example:

```c
var mother;
var father;

mother.var son;
father.var daughter;

mother.addChild("step-daughter", father.getChild("daughter"));

mother.addChild(Object());
var childrenArray.=(mother.getChildrenArray());
for (var it.=(childrenArray.begin()).!=, childrenArray.end(), it.++, {
    if (instanceOf(it.get(), Object), {
        basicOut(it.get().getName());
    });
});
```

#### Possible output:

```
son
daughter
Anonymous3384
```
