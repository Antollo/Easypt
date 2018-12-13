# `apply`

#### `..Root.apply`

Invoke the callable object f with elements of arr as arguments.

* **Parameters:** `Callable` f, `Array` arr 

* **Return value:** return value of f

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var arr.=(Array());
arr.pushBack(1);
arr.pushBack(2);
apply(basicOut, arr);
```