# `==`

#### `..Root.Array.==`

Compares elements of two arrays. 

* **Parameters:** another `Array`

* **Return value:**  new `Boolean`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto a.=(Array().pushBack(5.+(5), "a"));
auto b.=(Array().pushBack(10, "a"));

basicOut(a);
basicOut(b);
basicOut(a.==(b));

b.pushBack(3.14);
basicOut(a.==(b));
```

#### Expected output:

```
true
false
```