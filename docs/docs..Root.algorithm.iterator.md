# `iterator`

#### `..Root.algorithm.iterator`

Provides functions that operate on ranges of elements, please note that in range [first, last) last is pointing at element behind range.

## Child of:

[`algorithm`](docs..Root.algorithm.md)

## Signatures:

`Object`

## Members:

- [`merge`](docs..Root.algorithm.iterator.merge.md)
- [`copy`](docs..Root.algorithm.iterator.copy.md)
- [`move`](docs..Root.algorithm.iterator.move.md)
- [`sort`](docs..Root.algorithm.iterator.sort.md)
- [`forEach`](docs..Root.algorithm.iterator.forEach.md)


## Example:

```c
import("algorithm");

var a.=(Array());
a.pushBack("a", "b", "c");

var b.=(Array(3));

algorithm.iterator.copy(a.begin(), a.end(), b.begin());
basicOut(b);
```