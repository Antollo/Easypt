# `swap`

#### `..Root.algorithm.swap`

Swaps two objects (_warning: objects after swap are copies of original objects_).

* **Parameters:** `Object` a, `Object` b

* **Return value:** reference to second object

## Child of:

[`algorithm`](docs..Root.algorithm.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

auto a.=(1);
auto b.=(2);

algorithm.swap(a, b);
log(a, b);
```