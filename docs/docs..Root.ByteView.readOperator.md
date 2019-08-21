# `readOperator`

#### `..Root.ByteView.readOperator`

Returns iterator pointing to i-th byte. Read operator (`[]`) is shorthand for this function.

* **Parameters:** `Int` i

* **Return value:** new `ByteViewIterator`

## Child of:

[`ByteView`](docs..Root.ByteView.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("memory");

auto str.=("abc");
auto a.=(ByteView(str));

log(a.[1].get().toInt());
```