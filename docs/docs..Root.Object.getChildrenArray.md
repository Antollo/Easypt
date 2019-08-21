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
auto mother;
auto father;

mother.auto son;
father.auto daughter;

mother.addChild("step-daughter", father.getChild("daughter"));

mother.addChild(Object());
auto childrenArray.=(mother.getChildrenArray());
for (auto it.=(childrenArray.begin()).!=, childrenArray.end(), it.++, {
    if (instanceOf(it.get(), Object), {
        log(it.get().getName());
    });
});
```

#### Possible output:

```
son
daughter
Anonymous3384
```
