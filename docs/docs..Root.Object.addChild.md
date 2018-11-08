# `addChild`

#### `..Root.Object.addChild`

1. Add another object as child to this object (another object's parent do not change). 

2. Add another object as child with nickname nick to this object (another object's parent and name do not change). 

* **Parameters:**
    1. any type
    2. `String` nick, any type

* **Return value:**

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

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