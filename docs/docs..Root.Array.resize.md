# `resize`

#### `..Root.Array.resize`

Resizes the array to contain n elements.
If the current size is greater than n, the array is reduced to its first n elements. If n is greater than the current size, the array is extended by inserting at the end as many empty objects as needed to reach a size of n.

* **Parameters:** `Int` n

* **Return value:** reference to this `Array`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");
arr.resize(4);
arr[2].<-("ghi");
arr[3].<-("jkl");
basicOut(arr);
```