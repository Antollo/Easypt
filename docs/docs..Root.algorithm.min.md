# `min`

#### `..Root.algorithm.min`

Returns the smaller of the given variables (or first if they are equal) 

* **Parameters:** _`Type1`_ a, _`Type2`_ b ( _`Type1`_ must have `<=` method taking  _`Type2`_ instance as argument)

* **Return value:** smaller of a and b

## Child of:

[`algorithm`](docs..Root.algorithm.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

basicOut(algorithm.max(1, 2));
```