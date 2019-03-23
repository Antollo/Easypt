# `algorithm`

#### `..Root.algorithm`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Members:

- [**`iterator`**](docs..Root.algorithm.iterator.md) - _sort, forEach, ..._
- [`max`](docs..Root.algorithm.max.md)
- [`min`](docs..Root.algorithm.min.md)
- [`swap`](docs..Root.algorithm.swap.md)
- [`forEach`](docs..Root.algorithm.forEach.md)

## Example:

```c
import("algorithm");

auto a.=(Array());
a.pushBack("w", "a", "z", "f", "c", "d");
algorithm.iterator.sort(a.begin(), a.end(), {
    return(args[0].get().>(args[1].get()));
});
basicOut(a);
```