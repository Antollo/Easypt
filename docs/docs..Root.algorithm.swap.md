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

var a.=(1);
var b.=(2);

algorithm.swap(a, b);
basicOut(a, b);
```