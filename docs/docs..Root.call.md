# `call`

#### `..Root.call`

Invoke the callable object f with its remaining arguments as arguments and p as its parent.

* **Parameters:** any p, `Callable` f, _any number of any variables_

* **Return value:** return value of calling f

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
call(Root, basicOut, 1, 2);
```

_Equivalent of `Root.basicOut(1, 2);`._