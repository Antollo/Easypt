# `subarray`

#### `..Root.Array.subarray`

Returns new subarray that starts at element pointed by start and ends before element pointed by end.

* **Parameters:** `ArrayIterator` start, `ArrayIterator` end

* **Return value:** new `Array`

## Child of:

[`Array`](docs..Root.Array.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var arr.=(Array());
arr.pushBack("0");
arr.pushBack("1");
arr.pushBack("2");
arr.pushBack("3");
arr.pushBack("4");
basicOut(arr.subarray(arr.begin().+(1), arr.end().-(1)));
```

### Expected output:

```
1
2
3
```