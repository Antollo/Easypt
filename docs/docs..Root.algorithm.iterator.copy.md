# `copy`

#### `..Root.algorithm.iterator.copy`

Copies the elements in the range [first, last) to destination.

* **Parameters:** `Iterator` first, `Iterator` last, `Iterator` destination

* **Return value:** reference to destination

## Child of:

[`iterator`](docs..Root.algorithm.iterator.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

var a.=(Array());
a.pushBack("a", "b", "c");

var b.=(Array(3));

algorithm.iterator.copy(a.begin(), a.end(), b.begin());
basicOut(b);
```