# `forEach`

#### `..Root.algorithm.forEach`

Calls function sequentially with elements in the container as argument.

* **Parameters:** `Container` container, `Callable` function

* **Return value:** reference to value of `container.end()`

## Child of:

[`algorithm`](docs..Root.algorithm.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

auto a.=(Array());
a.pushBack("w", "a", "z", "f", "c", "d");
algorithm.forEach(a, log);
```