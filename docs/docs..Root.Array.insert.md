# `insert`

#### `..Root.Array.insert`

Inserts a copy of the sequence of elements in the range [first, last) before element pointed by e.

* **Parameters:** `ArrayIterator` e, `ArrayIterator` first, `ArrayIterator` last

* **Return value:** reference to this `Array`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");

auto numbers.=(Array().pushBack(1, 2, 3, 4, 5, 6, 7));

arr.insert(arr.begin(), numbers.begin(), numbers.end());
basicOut(arr);
```
