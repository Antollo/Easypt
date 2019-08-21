# `forEach`

#### `..Root.algorithm.iterator.forEach`

Calls function sequentially with elements in the range [first, last) as argument.

* **Parameters:** `Iterator` first, `Iterator` last, `Callable` function

* **Return value:** reference to last

## Child of:

[`iterator`](docs..Root.algorithm.iterator.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

auto a.=(Array());
a.pushBack("w", "a", "z", "f", "c", "d");
algorithm.iterator.forEach(a.begin(), a.end(), log);
```