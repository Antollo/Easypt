# `Object`

#### `..Root.Object`

Constructs new `Object`. Any variable created with keyword `var` is initialized with `Object` type.

* **Return value:** new `Object`

### `Object` type signatures:

`Object`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`debugTree`](docs..Root.Object.debugTree.md)
- [`=`](docs..Root.Object.=.md)
- [`<-`](docs..Root.Object.less-.md)
- [`merge`](docs..Root.Object.merge.md)
- [`getParent`](docs..Root.Object.getParent.md)
- [`getChild`](docs..Root.Object.getChild.md)
- [`getChildrenArray`](docs..Root.Object.getChildrenArray.md)
- [`hasChild`](docs..Root.Object.hasChild.md)
- [`addChild`](docs..Root.Object.addChild.md)
- [`removeChild`](docs..Root.Object.removeChild.md)
- [`getName`](docs..Root.Object.getName.md)
- [`copy`](docs..Root.Object.copy.md)
- [`!=`](docs..Root.Object.!=.md)
- [`===`](docs..Root.Object.===.md)

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
