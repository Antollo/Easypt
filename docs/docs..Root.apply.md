# `apply`

#### `..Root.apply`

Invoke the callable object f with elements of arr as arguments and p as its parent.

* **Parameters:** any p, `Callable` f, `Array` arr 

* **Return value:** return value of calling f

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack(1);
arr.pushBack(2);
apply(Root, basicOut, arr);
```

_Equivalent of `Root.basicOut(1, 2);`._