# `Object`

#### `..Root.Object`

Constructs new `Object`. Any variable created with keyword `auto` or `auto` is initialized with `Object` type.

* **Return value:** new `Object`

### `Object` type signatures:

`Object`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- [`debugTree`](docs..Root.Object.debugTree.md)
- [`=`](docs..Root.Object.=.md)
- [`getParent`](docs..Root.Object.getParent.md)
- [`getChild`](docs..Root.Object.getChild.md)
- [`getChildrenArray`](docs..Root.Object.getChildrenArray.md)
- [`hasChild`](docs..Root.Object.hasChild.md)
- [`addChild`](docs..Root.Object.addChild.md)
- [`removeChild`](docs..Root.Object.removeChild.md)
- [`getName`](docs..Root.Object.getName.md)
- [`setName`](docs..Root.Object.setName.md)
- [`copy`](docs..Root.Object.copy.md)
- [`!=`](docs..Root.Object.!=.md)
- [`===`](docs..Root.Object.===.md)

## Example:

```c
auto mother;
auto father;

mother.var son;
father.var daughter;

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
