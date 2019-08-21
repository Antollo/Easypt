# `addChild`

#### `..Root.Object.addChild`

1. Add another object as child to this object (another object's parent do not change). 

2. Add another object as child with nickname nick to this object (another object's name do not change). 

* **Parameters:**
    1. any type
    2. `String` nick, any type

* **Return value:** reference to this object

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

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