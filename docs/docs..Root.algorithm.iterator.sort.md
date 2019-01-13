# `sort`

#### `..Root.algorithm.iterator.sort`

Sorts the elements in the range [first, last) using order described by comparison.

**Time comlexity** `O(n*log(n))`

* **Parameters:** `Iterator` first, `Iterator` last, `Callable` comparison

* **Return value:** reference to last

## Child of:

[`iterator`](docs..Root.algorithm.iterator.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

var a.=(Array());
a.pushBack("w", "a", "z", "f", "c", "d");
algorithm.iterator.sort(a.begin(), a.end(), {
    return(args[0].get().>(args[1].get()));
});
basicOut(a);
```